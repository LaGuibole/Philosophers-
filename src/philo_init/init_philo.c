/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:32:33 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:32:53 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	init_forks(t_philo_ctx *ctx)
{
	unsigned int	i;

	ctx->forks = malloc(sizeof(pthread_mutex_t) * ctx->philo_count);
	if (!ctx->forks)
		return (print_error(ERR_ALLOC));
	i = 0;
	while (i < ctx->philo_count)
	{
		if (pthread_mutex_init(&ctx->forks[i], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&ctx->forks[--i]);
			free(ctx->forks);
			return (print_error(ERR_MUTEX));
		}
		i++;
	}
	return (RET_OK);
}

int	init_philosophers(t_philo_ctx *ctx)
{
	unsigned int	i;

	ctx->philos = malloc(sizeof(t_philo) * ctx->philo_count);
	if (!ctx->philos)
		return (print_error(ERR_ALLOC));
	i = 0;
	while (i < ctx->philo_count)
	{
		ctx->philos[i].id = i + 1;
		ctx->philos[i].is_dead = false;
		ctx->philos[i].times_eaten = 0;
		ctx->philos[i].last_time_eaten = ctx->start_time;
		ctx->philos[i].ctx = ctx;
		if (pthread_mutex_init(&ctx->philos[i].mutex_eating, NULL) != 0
			|| pthread_mutex_init(&ctx->philos[i].mutex_eaten, NULL) != 0)
		{
			clean_philo_mutex_error(ctx, i);
			return (print_error(ERR_MUTEX));
		}
		ctx->philos[i].l_fork = &ctx->forks[i];
		ctx->philos[i].r_fork = &ctx->forks[(i + 1) % ctx->philo_count];
		i++;
	}
	return (RET_OK);
}
