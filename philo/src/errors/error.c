/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:50:29 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/02 11:08:28 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	print_error(char *msg)
{
	fd_printf(STDERR_FILENO, "%s%s%s\n", RED, msg, RESET);
	return (RET_ERR);
}
