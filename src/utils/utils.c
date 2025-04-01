/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:59:39 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:35:29 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	custom_sleep(long long ms)
{
	long long	start;
	long long	current;

	start = get_current_time();
	while (1)
	{
		current = get_current_time();
		if (current - start >= ms)
			break ;
		usleep(100);
	}
}

void	print_status(t_philo *philo, t_state state)
{
	t_philo_ctx	*ctx;
	long long	current_time;

	ctx = (t_philo_ctx *)philo->ctx;
	if (!is_running(ctx))
		return ;
	current_time = get_current_time() - ctx->start_time;
	pthread_mutex_lock(&ctx->mutex_print);
	if (state == STATE_FORK_TAKEN)
		printf("%lld %d has taken a fork\n", current_time, philo->id);
	else if (state == STATE_EATING)
		printf("%lld %d is eating\n", current_time, philo->id);
	else if (state == STATE_SLEEPING)
		printf("%lld %d is sleeping\n", current_time, philo->id);
	else if (state == STATE_THINKING)
		printf ("%lld %d is thinking\n", current_time, philo->id);
	else if (state == STATE_DIED)
		printf("%lld %d died\n", current_time, philo->id);
	pthread_mutex_unlock(&ctx->mutex_print);
}
