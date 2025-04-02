/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:30:01 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:35:38 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	check_philosopher_death(t_philo *philo)
{
	t_philo_ctx	*ctx;
	long long	last_meal_time;
	long long	current_time;

	ctx = (t_philo_ctx *)philo->ctx;
	current_time = get_current_time();
	pthread_mutex_lock(&philo->mutex_eating);
	last_meal_time = philo->last_time_eaten;
	pthread_mutex_unlock(&philo->mutex_eating);
	if (current_time - last_meal_time > ctx->timers.death)
		return (true);
	return (false);
}

void	signal_death(t_philo *philo, t_philo_ctx *ctx)
{
	print_status(philo, STATE_DIED);
	set_running(ctx, false);
}

bool	check_all_eaten(t_philo_ctx *ctx)
{
	unsigned int	i;
	unsigned int	times_eaten;
	bool			all_eaten;

	all_eaten = true;
	i = 0;
	while (i < ctx->philo_count)
	{
		pthread_mutex_lock(&ctx->philos[i].mutex_eaten);
		times_eaten = ctx->philos[i].times_eaten;
		pthread_mutex_unlock(&ctx->philos[i].mutex_eaten);
		if (times_eaten < ctx->timers.each)
		{
			all_eaten = false;
			break ;
		}
		i++;
	}
	return (all_eaten);
}
