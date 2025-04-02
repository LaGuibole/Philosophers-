/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:10:29 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:12:13 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	is_running(t_philo_ctx *ctx)
{
	bool	is_running;

	pthread_mutex_lock(&ctx->mutex_is_running);
	is_running = ctx->is_running;
	pthread_mutex_unlock(&ctx->mutex_is_running);
	return (is_running);
}

void	set_running(t_philo_ctx *ctx, bool state)
{
	pthread_mutex_lock(&ctx->mutex_is_running);
	ctx->is_running = state;
	pthread_mutex_unlock(&ctx->mutex_is_running);
}
