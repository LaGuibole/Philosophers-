/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:48:30 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:08:17 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	clean_philosophers(t_philo_ctx *ctx)
{
	unsigned int	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		pthread_mutex_destroy(&ctx->philos[i].mutex_eating);
		pthread_mutex_destroy(&ctx->philos[i].mutex_eaten);
		i++;
	}
	free(ctx->philos);
}

void	clean_forks(t_philo_ctx *ctx)
{
	unsigned int	i;

	i = 0;
	while (i < ctx->philo_count)
		pthread_mutex_destroy(&ctx->forks[i++]);
	free(ctx->forks);
}

void	clean_context(t_philo_ctx *ctx)
{
	pthread_mutex_destroy(&ctx->mutex_is_running);
	pthread_mutex_destroy(&ctx->mutex_print);
	pthread_mutex_destroy(&ctx->mutex_someone_died);
	if (ctx->forks)
		clean_forks(ctx);
	if (ctx->philos)
		clean_philosophers(ctx);
}
