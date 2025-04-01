/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:47:01 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 17:05:58 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	take_forks(t_philo *philo)
{
	// t_philo_ctx *ctx = (t_philo_ctx *)philo->ctx;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, STATE_FORK_TAKEN);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, STATE_FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, STATE_FORK_TAKEN);
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, STATE_FORK_TAKEN);
	}
}

void	eat(t_philo *philo)
{
	t_philo_ctx *ctx = (t_philo_ctx *)philo->ctx;
	pthread_mutex_lock(&philo->mutex_eating);
	philo->last_time_eaten = get_current_time();
	pthread_mutex_unlock(&philo->mutex_eating);
	print_status(philo, STATE_EATING);
	custom_sleep(ctx->timers.eat);
	pthread_mutex_lock(&philo->mutex_eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->mutex_eaten);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	think(t_philo *philo)
{
	print_status(philo, STATE_THINKING);
	usleep(500);
}

void	sleep_philosophers(t_philo *philo)
{
	t_philo_ctx *ctx = (t_philo_ctx *)philo->ctx;
	print_status(philo, STATE_SLEEPING);
	custom_sleep(ctx->timers.sleep);
}
