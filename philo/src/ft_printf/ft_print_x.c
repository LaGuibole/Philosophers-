/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:37:51 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/02 10:54:52 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static	int	ft_print_hexa(int fd, unsigned int n, char *car)
{
	if (n >= 16)
		return (ft_print_hexa(fd, n / 16, car) + ft_print_hexa(fd, n % 16, car));
	return (ft_print_c(fd, car[n]));
}

int	ft_print_x(int fd, unsigned int n, int format)
{
	char	*chars;

	chars = L_HEX_CHARSET;
	if (format == 'X')
		chars = U_HEX_CHARSET;
	return (ft_print_hexa(fd, n, chars));
}
