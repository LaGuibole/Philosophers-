/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:47:01 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/02 09:58:59 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, STATE_FORK_TAKEN);
		if (philo->l_fork == philo->r_fork)
			return ;
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, STATE_FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, STATE_FORK_TAKEN);
		if (philo->l_fork == philo->r_fork)
			return ;
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, STATE_FORK_TAKEN);
	}
}

void	eat(t_philo *philo, t_philo_ctx *ctx)
{
	take_forks(philo);
	if (philo->r_fork != philo->l_fork)
	{
		pthread_mutex_lock(&philo->mutex_eating);
		philo->last_time_eaten = get_current_time();
		pthread_mutex_unlock(&philo->mutex_eating);
		print_status(philo, STATE_EATING);
		custom_sleep(ctx->timers.eat);
		pthread_mutex_lock(&philo->mutex_eaten);
		philo->times_eaten++;
		pthread_mutex_unlock(&philo->mutex_eaten);
	}
	release_forks(philo);
}

void	release_forks(t_philo *philo)
{
	if (philo->l_fork == philo->r_fork)
		pthread_mutex_unlock(philo->l_fork);
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	sleep_philosophers(t_philo *philo)
{
	t_philo_ctx	*ctx;

	ctx = (t_philo_ctx *)philo->ctx;
	print_status(philo, STATE_SLEEPING);
	custom_sleep(ctx->timers.sleep);
}
