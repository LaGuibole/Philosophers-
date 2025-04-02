/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:06:27 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/02 10:54:42 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	print_d(int fd, long n)
{
	if (n >= 10)
		return (print_d(fd, n / 10) + print_d(fd, n % 10));
	return (ft_print_c(fd, n + '0'));
}

int	ft_print_d(int fd, int n)
{
	long	_n;

	_n = n;
	if (n < 0)
		return (write(fd, "-", 1) + print_d(fd, -_n));
	return (print_d(fd, _n));
}
