/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:57:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/06 21:03:06 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static long	ft_white_long(const char *s)
{
	long	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\v'
		|| s[i] == '\f' || s[i] == '\r')
		i++;
	return (i);
}

static long	ft_isdigit_long(long c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

long	ft_atoi_long(const char *nptr)
{
	long	i;
	long	sign;
	long	result;

	i = ft_white_long(nptr);
	sign = 1;
	result = 0;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_isdigit_long(nptr[i]))
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	result *= sign;
	if (result > 2147483647)
		return (-1);
	return (result * sign);
}
