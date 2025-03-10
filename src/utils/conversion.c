/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:55:22 by guphilip          #+#    #+#             */
/*   Updated: 2025/03/10 17:36:13 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoui(const char *str, unsigned int *ptr_value)
{
	unsigned int	value;
	int				i;

	if (*str == '\0')
		return (0);
	value = 0;
	i = 0;
	while (is_digit(str[i]))
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	*ptr_value = value;
	return (str[i] == '\0');
}

int ft_atot(const char *str, time_t *ptr_time)
{
	time_t	time;
	int		i;

	if (*str == '\0')
		return (0);
	time = 0;
	i = 0;
	while (is_digit(str[i]))
	{
		time = time * 10 + str[i] - '0';
		i++;
	}
	*ptr_time = time;
	return (str[i] == '\0');
}
