/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:49:36 by guphilip          #+#    #+#             */
/*   Updated: 2025/03/31 11:38:17 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_philo_ctx	ctx;

	if (parse_args(argc, argv, &ctx) == RET_ERR)
		return (EXIT_FAILURE);
	printf(GREEN "Program: %s\nPhilosophers: %u\nTime to die: %ld\nTime to eat: %ld\nTime to sleep: %ld\nTimes to eat: %u\n" RESET,
		ctx.program_name, ctx.philo_count, ctx.timers.death, ctx.timers.eat, ctx.timers.sleep, ctx.timers.each);
	return (EXIT_SUCCESS);
}
