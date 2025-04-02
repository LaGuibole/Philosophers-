/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:54:01 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:25:24 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo		*philo;
	t_philo_ctx	*ctx;

	philo = (t_philo *)arg;
	ctx = (t_philo_ctx *)philo->ctx;
	if (philo->id % 2 == 0)
		custom_sleep(ctx->timers.eat / 2);
	while (is_running(ctx))
	{
		eat(philo, ctx);
		if (!is_running(ctx))
			break ;
		print_status(philo, STATE_THINKING);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_philo_ctx		*ctx;
	unsigned int	i;

	ctx = (t_philo_ctx *)arg;
	while (is_running(ctx))
	{
		i = 0;
		while (i < ctx->philo_count)
		{
			if (check_philosopher_death(&ctx->philos[i]))
				signal_death(&ctx->philos[i], ctx);
			if (ctx->timers.each > 0 && check_all_eaten(ctx))
				set_running(ctx, false);
			i++;
		}
		usleep(50);
	}
	return (NULL);
}
