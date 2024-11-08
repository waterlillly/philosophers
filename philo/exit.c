/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:19:14 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/08 17:12:00 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death(t_philo *p)
{
	pthread_mutex_unlock(&p->sim->write_x);
	printf("\033[0;35m%ld %d died\033[0m\n", cur_time(p), p->id + 1);
	pthread_mutex_lock(&p->sim->write_x);
	p->sim->stop = true;
}

int	free_and_destroy_mutexes(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->sim->nop)
	{
		if (pthread_mutex_destroy(&p->sim->forkx[i]))
		{
			printf("\033[0;31merr_ex: pthread_mutex_destroy(forkx)\033[0m\n");
			return (1);
		}
		if (pthread_mutex_destroy(&p[i].px))
		{
			printf("\033[0;31merr_ex: pthread_mutex_destroy(px)\033[0m\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_threads(t_philo *p)
{
	int	i;

	i = -1;
	if (!p)
		return (1);
	while (++i < p->sim->nop)
	{
		if (p->sim && p[i].ptid)
		{
			if (pthread_join(p[i].ptid, NULL))
			{
				printf("\033[0;31merr_ex: pthread_join ptid\033[0m\n");
				return (1);
			}
		}
	}
	if (p->sim && p->sim->monitor)
	{
		if (pthread_join(p->sim->monitor, NULL))
		{
			printf("\033[0;31merr_ex: pthread_join monitor\033[0m\n");
			return (1);
		}
	}
	return (0);
}

int	err_ex(const char *err, t_philo *p, t_sim *sim)
{
	int	i;

	i = 0;
	if (err)
	{
		write_x_smth(sim, (char *)err);
		pthread_mutex_lock(&sim->stopx);
		sim->stop = true;
		pthread_mutex_unlock(&sim->stopx);
	}
	if (pthread_mutex_destroy(&sim->write_x) == -1)
		return (printf("\033[0;31merr_ex: pthread_mutex_destroy"
				"(write_x)\033[0m\n"), 1);
	if (pthread_mutex_destroy(&sim->stopx) == -1)
		return (printf("\033[0;31merr_ex: pthread_mutex_destroy"
				"(stopx)\033[0m\n"), 1);
	if (sim && sim->forkx)
		free_and_destroy_mutexes(p);
	if (p)
		free(p);
	if (sim && sim->forkx)
		free(sim->forkx);
	if (err)
		return (1);
	return (0);
}
