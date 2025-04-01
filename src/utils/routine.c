/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:54:01 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 17:06:33 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_philo_ctx *ctx = (t_philo_ctx *)philo->ctx;
	bool running;

	if (philo->id % 2 == 0)
		custom_sleep(ctx->timers.eat / 2);
	while (1)
	{
		pthread_mutex_lock(&ctx->mutex_is_running);
		running = ctx->is_running;
		pthread_mutex_unlock(&ctx->mutex_is_running);
		if (!running)
			break ;
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_philosophers(philo);
		think(philo);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo_ctx *ctx = (t_philo_ctx *)arg;
	unsigned int	i;
	bool running = true;

	while (running)
	{
		i = 0;
		while (i < ctx->philo_count && running)
		{
			if (check_philosopher_death(&ctx->philos[i]))
			{
				signal_death(&ctx->philos[i]);
				running = false;
			}
			if (ctx->timers.each > 0 && check_all_eaten(ctx))
			{
				pthread_mutex_lock(&ctx->mutex_is_running);
				ctx->is_running = false;
				pthread_mutex_unlock(&ctx->mutex_is_running);
				running = false;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
