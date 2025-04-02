/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:33:20 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:33:35 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	init_simulation(t_philo_ctx *ctx)
{
	if (init_threads(ctx) != RET_OK)
	{
		clean_philosophers(ctx);
		clean_forks(ctx);
		clean_context(ctx);
		return (RET_ERR);
	}
	return (RET_OK);
}

int	create_monitor_thread(t_philo_ctx *ctx)
{
	pthread_t		monitor;
	unsigned int	i;

	if (pthread_create(&monitor, NULL, monitor_routine, ctx) != 0)
	{
		pthread_mutex_lock(&ctx->mutex_is_running);
		ctx->is_running = false;
		pthread_mutex_unlock(&ctx->mutex_is_running);
		i = 0;
		while (i < ctx->philo_count)
			pthread_join(ctx->philos[i++].thread_id, NULL);
		return (print_error(ERR_THREAD_INIT));
	}
	pthread_join(monitor, NULL);
	return (RET_OK);
}
