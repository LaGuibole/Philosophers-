/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:49:36 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:34:25 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int	main(int argc, char **argv)
// {
// 	t_philo_ctx	ctx;

// 	if (parse_args(argc, argv, &ctx) == RET_ERR)
// 		return (EXIT_FAILURE);
// 	printf(GREEN "Program: %s\nPhilosophers: %u\nTime to die: %ld\nTime to eat: %ld\nTime to sleep: %ld\nTimes to eat: %d\n" RESET,
// 		ctx.program_name, ctx.philo_count, ctx.timers.death, ctx.timers.eat, ctx.timers.sleep, ctx.timers.each);
// 	return (EXIT_SUCCESS);
// }

int main(int argc, char **argv)
{
    t_philo_ctx ctx;

	ctx = (t_philo_ctx){};
    // Sauvegarder le nom du programme
    ctx.program_name = argv[0];

    // Analyser les arguments
    if (parse_args(argc, argv, &ctx) != RET_OK)
        return (RET_ERR);

    // Initialiser le contexte
    if (init_context(&ctx) != RET_OK)
    {
        clean_context(&ctx);
        return (RET_ERR);
    }

    // Initialiser les fourchettes (mutex)
    if (init_forks(&ctx) != RET_OK)
    {
        clean_context(&ctx);
        return (RET_ERR);
    }

    // Initialiser les philosophes
    if (init_philosophers(&ctx) != RET_OK)
    {
        clean_context(&ctx);
        return (RET_ERR);
    }

    // Démarrer la simulation
    if (init_simulation(&ctx) != RET_OK)
    {
        clean_context(&ctx);
        return (RET_ERR);
    }

    // Attendre que tous les threads se terminent
    for (unsigned int i = 0; i < ctx.philo_count; i++)
    {
        if (pthread_join(ctx.philos[i].thread_id, NULL) != 0)
        {
            printf("%sÉchec lors de l'attente du thread %d%s\n", RED, i + 1, RESET);
        }
    }

    // Nettoyer les ressources
    clean_context(&ctx);
    return (RET_OK);
}
