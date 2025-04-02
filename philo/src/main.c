/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:49:36 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/02 12:02:22 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int  wait_philosophers(t_philo_ctx *ctx)
{
	unsigned int	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		if (pthread_join(ctx->philos[i].thread_id, NULL) != 0)
		{
			fd_printf(STDERR_FILENO, "%sThread waiting failed %d&s\n",
				RED, i + 1, RESET);
			return (RET_ERR);
		}
		i++;
	}
	return (RET_OK);
}

int main(int argc, char **argv)
{
	t_philo_ctx ctx;

	ctx = (t_philo_ctx){};
	ctx.program_name = argv[0];
	if (parse_args(argc, argv, &ctx) != RET_OK)
		return (RET_ERR);
	if (init_context(&ctx) != RET_OK)
		return (clean_context(&ctx), RET_ERR);
	if (init_forks(&ctx) != RET_OK)
		return (clean_context(&ctx), RET_ERR);
	if (init_philosophers(&ctx) != RET_OK)
		return (clean_context(&ctx), RET_ERR);
	if (init_simulation(&ctx) != RET_OK || wait_philosophers(&ctx) != RET_OK)
		return(clean_context(&ctx), RET_ERR);
	clean_context(&ctx);
	return (RET_OK);
}
