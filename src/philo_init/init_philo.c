/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:22:16 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:05:45 by guphilip         ###   ########.fr       */
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
		return(print_error(ERR_THREAD_INIT));
	}
	pthread_join(monitor, NULL);
	return (RET_OK);
}

int init_threads(t_philo_ctx *ctx)
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

int	init_simulation(t_philo_ctx *ctx)
{
	if (init_context(ctx) != RET_OK)
		return (RET_ERR);
	if (init_forks(ctx) != RET_OK)
	{
		clean_context(ctx);
		return (RET_ERR);
	}
	if (init_philosophers(ctx) != RET_OK)
	{
		clean_forks(ctx);
		clean_context(ctx);
		return (RET_ERR);
	}
	if (init_threads(ctx) != RET_OK)
	{
		clean_philosophers(ctx);
		clean_forks(ctx);
		clean_context(ctx);
		return (RET_ERR);
	}
	return (RET_OK);
}
