/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:38:33 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/02 10:54:50 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_print_u(int fd, unsigned int n)
{
	if (n >= 10)
		return (ft_print_u(fd, n / 10) + ft_print_u(fd, n % 10));
	return (ft_print_c(fd, n + '0'));
}
