/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:45:49 by guphilip          #+#    #+#             */
/*   Updated: 2025/03/31 15:59:49 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	clean_philo_mutex_error(t_philo_ctx *ctx, unsigned int i)
{
	while (i > 0)
	{
		pthread_mutex_destroy(&ctx->philos[--i].mutex_eating);
		pthread_mutex_destroy(&ctx->philos[i].mutex_eaten);
	}
	free(ctx->philos);
}

void	clean_forks_error(t_philo_ctx *ctx, unsigned int i)
{
	while (i > 0)
		pthread_mutex_destroy(&ctx->forks[--i]);
	free(ctx->forks);
}

void	handle_thread_error(t_philo_ctx *ctx, unsigned int i)
{
	pthread_mutex_lock(&ctx->mutex_is_running);
	ctx->is_running = false;
	pthread_mutex_lock(&ctx->mutex_is_running);

	while (i > 0)
		pthread_join(ctx->philos[--i].thread_id, NULL);
}
