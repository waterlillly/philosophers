/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   early_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:03:11 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/08 16:11:17 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads_gracefully(t_philo *p, int i)
{
	if (!p)
		return ;
	while (--i >= 0)
	{
		if (p->sim && p[i].ptid)
		{
			if (pthread_join(p[i].ptid, NULL))
			{
				printf("\033[0;31merr_ex: pthread_join ptid\033[0m\n");
				return ;
			}
		}
	}
}

int	exit_gracefully(t_sim *sim, t_philo *p, int i, const char *err)
{
	pthread_mutex_lock(&sim->stopx);
	sim->stop = true;
	pthread_mutex_unlock(&sim->stopx);
	join_threads_gracefully(p, i);
	if (err)
		write_x_smth(sim, (char *)err);
	if (pthread_mutex_destroy(&sim->write_x))
	{
		printf("\033[0;31merr_ex: pthread_mutex_destroy(write_x)\033[0m\n");
		return (1);
	}
	if (pthread_mutex_destroy(&sim->stopx))
	{
		printf("\033[0;31merr_ex: pthread_mutex_destroy(stopx)\033[0m\n");
		return (1);
	}
	free_and_destroy_mutexes(p);
	if (p)
		free(p);
	if (sim->forkx)
		free(sim->forkx);
	return (1);
}

static int	destroy_mutexes_gracefully(t_sim *sim, int i)
{
	if (!sim->forkx)
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_destroy(&sim->forkx[i]))
		{
			printf("\033[0;31merr_ex: pthread_mutex_destroy(forkx)\033[0m\n");
			return (1);
		}
	}
	return (0);
}

int	exit_gracefully_no_threads(t_sim *sim, t_philo *p, int i, const char *err)
{
	if (err)
		write_x_smth(sim, (char *)err);
	pthread_mutex_lock(&sim->stopx);
	sim->stop = true;
	pthread_mutex_unlock(&sim->stopx);
	if (pthread_mutex_destroy(&sim->write_x))
	{
		printf("\033[0;31merr_ex: pthread_mutex_destroy(write_x)\033[0m\n");
		return (1);
	}
	if (pthread_mutex_destroy(&sim->stopx))
	{
		printf("\033[0;31merr_ex: pthread_mutex_destroy(stopx)\033[0m\n");
		return (1);
	}
	destroy_mutexes_gracefully(sim, i);
	if (p)
		free(p);
	if (sim->forkx)
		free(sim->forkx);
	return (1);
}
