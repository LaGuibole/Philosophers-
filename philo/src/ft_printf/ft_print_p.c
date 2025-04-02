/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:53:01 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/02 10:54:45 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	ft_print_ptr(int fd, uintptr_t ptr)
{
	if (ptr >= 16)
		return (ft_print_ptr(fd, ptr / 16) + ft_print_ptr(fd, ptr % 16));
	return (ft_print_c(fd, L_HEX_CHARSET[ptr]));
}

int	ft_print_p(int fd, uintptr_t ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (ft_print_s(fd, "(nil)"));
	i += ft_print_s(fd, "0x");
	i += ft_print_ptr(fd, ptr);
	return (i);
}

// int	main(void)
// {
// 	char	*ptr;

// 	ptr = "Bonjour";
// 	ft_print_ptr("\n%p", ptr);
// 	printf("\n%p", ptr);
// }
