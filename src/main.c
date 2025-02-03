/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:55:31 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/04 16:09:11 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_sim	sim;
	t_philo	*p;

	if (!check_args(ac, av))
	{
		ft_putendl_fd("\033[0;31mInvalid arguments.\n"
			"./philos <number_of_philosophers>"
			" <time_to_die> <time_to_eat> <time_to_sleep>"
			" [number_of_times_each_philosopher_must_eat]\n\033[0m", 2);
		return (1);
	}
	memset(&sim, 0, sizeof(t_sim));
	p = init_input(&sim, ac, av);
	if (!p)
		return (1);
	err_ex(NULL, p, &sim);
	return (0);
}
