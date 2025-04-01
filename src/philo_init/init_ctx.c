/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:22:16 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:33:38 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	init_context(t_philo_ctx *ctx)
{
	if (pthread_mutex_init(&ctx->mutex_is_running, NULL) != 0)
		return (print_error(ERR_MUTEX));
	if (pthread_mutex_init(&ctx->mutex_print, NULL) != 0)
	{
		pthread_mutex_destroy(&ctx->mutex_is_running);
		return (print_error(ERR_MUTEX));
	}
	if (pthread_mutex_init(&ctx->mutex_someone_died, NULL) != 0)
	{
		pthread_mutex_destroy(&ctx->mutex_is_running);
		pthread_mutex_destroy(&ctx->mutex_print);
		return (print_error(ERR_MUTEX));
	}
	ctx->is_running = true;
	ctx->someone_died = false;
	ctx->start_time = get_current_time();
	return (RET_OK);
}

int	init_threads(t_philo_ctx *ctx)
{
	unsigned int	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		if (pthread_create(&ctx->philos[i].thread_id, NULL,
				philosopher_routine, &ctx->philos[i]) != 0)
		{
			handle_thread_error(ctx, i);
			return (print_error(ERR_THREAD_INIT));
		}
		i++;
	}
	if (create_monitor_thread(ctx) != RET_OK)
		return (RET_ERR);
	return (RET_OK);
}
