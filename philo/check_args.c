/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:14:03 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/08 17:11:09 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_check_arg(int ac, char **in)
{
	char	*tmp;
	int		x;

	x = 1;
	if (x == ac)
		return (false);
	while (x < ac)
	{
		tmp = ft_itoa_long(ft_atoi_long(in[x]));
		if (!tmp)
			return (false);
		if (ft_strcmp_bool(tmp, in[x]))
		{
			free(tmp);
			tmp = NULL;
			x++;
		}
		else
			return (free(tmp), tmp = NULL, false);
	}
	return (true);
}

bool	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6 || !ft_check_arg(ac, av))
		return (false);
	if (ft_atoi_long(av[1]) <= 0 || ft_atoi_long(av[2]) <= 0
		|| ft_atoi_long(av[3]) <= 0 || ft_atoi_long(av[4]) <= 0)
		return (false);
	if (av[1][0] == '-' || ft_strlen(av[1]) > 3 || ft_atoi_long(av[1]) > 200)
	{
		if (ft_atoi_long(av[1]) > 500)
		{
			ft_putendl_fd("\033[0;31mMax philosophers: 500\033[0m", 2);
			return (false);
		}
		ft_putendl_fd("\033[0;31mPretty sure we should only test up to 200"
			" philosophers, but here you go... :)\033[0m\n", 2);
	}
	if (av[5] && ft_atoi_long(av[5]) <= 0)
		return (false);
	return (true);
}
