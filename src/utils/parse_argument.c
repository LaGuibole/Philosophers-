/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:46:01 by guphilip          #+#    #+#             */
/*   Updated: 2025/03/31 11:52:16 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/// @brief Check if the char is a digit
/// @param n Char to be checked
/// @return 1 on success, 0 otherwise
int	is_digit(int n)
{
	return (n >= '0' && n <= '9');
}

/// @brief Atoi function but treats long int
/// @param str The parameter that will be checked
/// @return -1 on error, the number otherwise
long	ft_atol(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (!str || !str[0])
		return (-1);
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (-1);
		res = res * 10 + str[i] - '0';
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	return (res);
}

/// @brief Parse each parameter with atol
/// @param arg The parameter to be checked
/// @param dest Pointer to the parameter
/// @param err_msg Error message
/// @return 0 on succes, 1 otherqwise
int	parse_value(char *arg, long *dest, char *err_msg)
{
	*dest = ft_atol(arg);
	if (*dest == -1)
	{
		printf(RED "Error: %s " ERR_NAT_INT "\n" RESET, err_msg);
		return (RET_ERR);
	}
	return (RET_OK);
}

/// @brief Main monitor for parsing arguments
/// @param argc Number of program's args
/// @param argv Number of program's parameters
/// @param ctx Pointer to the philo_ctx stuct
/// @return An error if a parameter is not a natural int, 0 otherwisae
int	parse_args(int argc, char **argv, t_philo_ctx *ctx)
{
	if (argc < PROG__MIN || argc > PROG__MAX)
		return (printf(RED "Error: Invalid number of arguments\n" RESET),
			RET_ERR);
	ctx->program_name = argv[PROG_NAME];
	if (parse_value(argv[PROG_PHILO_COUNT], (long *)&ctx->philo_count, ARG1)
		|| parse_value(argv[PROG_DEATH_TIMER], &ctx->timers.death, ARG2)
		|| parse_value(argv[PROG_EAT_TIMER], &ctx->timers.eat, ARG3)
		|| parse_value(argv[PROG_SLEEP_TIMER], &ctx->timers.sleep, ARG4))
		return (RET_ERR);
	if (argc == PROG__MAX)
	{
		if (parse_value(argv[PROG_EACHP_TIMER],
				(long *)&ctx->timers.each, ARG5))
			return (RET_ERR);
	}
	else
		ctx->timers.each = INT_MAX;
	return (RET_OK);
}
