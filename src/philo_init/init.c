/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:46:57 by guphilip          #+#    #+#             */
/*   Updated: 2025/03/10 17:51:02 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_philo_ctx *ctx, int argc, char **argv)
{
	ctx->program_name = argv[PROG_NAME];
	ctx->philos = NULL;
	ctx->is_running = false;
	ctx->forks = NULL;
	if (!ft_atoui(argv[PROG_PHILO_COUNT], &ctx->philo_count))
		error(ctx, ARG1 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_DEATH_TIMER], &ctx->timers.death))
		error(ctx, ARG2 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_EAT_TIMER], &ctx->timers.eat))
		error(ctx, ARG3 " " ERR_NAT_INT);
	if (!ft_atot(argv[PROG_SLEEP_TIMER], &ctx->timers.sleep))
		error(ctx, ARG4 " " ERR_NAT_INT);
	if (argc != PROG__MAX && !ft_atoui(argv[PROG_EACHP_TIMER]))
}
