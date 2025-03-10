/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:19:03 by guphilip          #+#    #+#             */
/*   Updated: 2025/03/10 17:30:47 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(t_philo_ctx *ctx, const char *message)
{
	printf("%s%s : %s%s\n", RED, ctx->program_name, message, RESET);
	philo_destroy(&ctx);
	exit(RET_ERR);
}
