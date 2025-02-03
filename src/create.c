/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:18:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2025/02/03 13:58:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_monitor(t_sim *sim, t_philo *p)
{
	if (pthread_create(&sim->monitor, NULL, &monitoring, p))
		return (err_ex("pthread_t create monitor failed", p, sim), 1);
	return (0);
}

int	create_philos(t_sim *sim, t_philo *p)
{
	int	i;

	i = 0;
	init_philos(p, sim);
	sim->start = get_time();
	while (i < sim->nop)
	{
		p[i].id = i;
		if (pthread_create(&p[i].ptid, NULL, &routine, &p[i]))
			return (exit_gracefully(sim, p, i, "pthread_create philo failed"),
				1);
		i++;
	}
	if (create_monitor(sim, p))
		return (1);
	if (join_threads(p))
		return (1);
	return (0);
}

int	create_x(t_sim *sim, t_philo *p)
{
	if (pthread_mutex_init(&sim->write_x, NULL))
		return (free(p), 1);
	if (pthread_mutex_init(&sim->stopx, NULL))
	{
		pthread_mutex_destroy(&sim->write_x);
		return (free(p), 1);
	}
	return (0);
}

int	create_forks(t_sim *sim, t_philo *p)
{
	int	i;

	i = 0;
	sim->forkx = malloc(sizeof(pthread_mutex_t) * sim->nop);
	if (!sim->forkx)
		return (err_ex("pthread_mutex_t malloc forks failed", p, sim), 1);
	while (i < sim->nop)
	{
		if (pthread_mutex_init(&sim->forkx[i], NULL))
			return (exit_gracefully_no_threads(sim, p, i,
					"pthread_mutex_init forks failed"));
		i++;
	}
	return (0);
}
