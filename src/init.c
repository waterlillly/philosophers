/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:14:39 by lbaumeis          #+#    #+#             */
/*   Updated: 2025/02/03 13:58:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*init_input(t_sim *sim, int ac, char **av)
{
	t_philo	*p;

	sim->nop = ft_atoi_long(av[1]);
	sim->ttd = ft_atoi_long(av[2]);
	sim->tte = ft_atoi_long(av[3]);
	sim->tts = ft_atoi_long(av[4]);
	if (ac == 6)
		sim->mte = ft_atoi_long(av[5]);
	else
		sim->mte = -1;
	sim->stop = false;
	if (sim->nop > 0)
	{
		p = malloc(sizeof(t_philo) * sim->nop);
		if (!p)
			return (NULL);
		if (create_x(sim, p))
			return (NULL);
		if (create_forks(sim, p))
			return (NULL);
		if (create_philos(sim, p))
			return (NULL);
		return (p);
	}
	return (NULL);
}

int	init_philos(t_philo *p, t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nop)
	{
		p[i].sim = sim;
		if (sim->nop == 1)
			p[i].fork_r = i;
		else if (i <= sim->nop - 2)
		{
			p[i].fork_r = i;
			p[i].fork_l = i + 1;
		}
		else
		{
			p[i].fork_r = (i + 1) % sim->nop;
			p[i].fork_l = i;
		}
		p[i].mc = 0;
		p[i].done = false;
		p[i].last_meal = -1;
		if (pthread_mutex_init(&p[i].px, NULL))
			return (err_ex("pthread mutex init failed", p, sim), 1);
	}
	return (0);
}
