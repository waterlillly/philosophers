/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:15:55 by lbaumeis          #+#    #+#             */
/*   Updated: 2025/02/03 13:58:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	monitoring_the_dead(t_philo *p, int x)
{
	pthread_mutex_lock(&p->sim->stopx);
	p->sim->stop = true;
	pthread_mutex_unlock(&p->sim->stopx);
	pthread_mutex_lock(&p->sim->write_x);
	printf("\033[0;35m%ld %d died\033[0m\n", cur_time(p), x + 1);
	pthread_mutex_unlock(&p->sim->write_x);
}

static bool	monitoring_loop(t_philo *p, int x, int *counter)
{
	pthread_mutex_lock(&p[x].px);
	if (cur_time(p) - p[x].last_meal >= p->sim->ttd)
	{
		pthread_mutex_unlock(&p[x].px);
		monitoring_the_dead(p, x);
		return (false);
	}
	else if (p[x].done == true)
	{
		pthread_mutex_unlock(&p[x].px);
		(*counter)++;
	}
	else
		pthread_mutex_unlock(&p[x].px);
	return (true);
}

void	*monitoring(void *arg)
{
	int		x;
	int		counter;
	t_philo	*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->sim->stopx);
	while (p->sim->stop == false)
	{
		pthread_mutex_unlock(&p->sim->stopx);
		x = -1;
		counter = 0;
		while (++x < p->sim->nop)
		{
			if (!monitoring_loop(p, x, &counter))
				break ;
		}
		if (counter >= p->sim->nop)
		{
			p->sim->stop = true;
			break ;
		}
		pthread_mutex_lock(&p->sim->stopx);
	}
	pthread_mutex_unlock(&p->sim->stopx);
	return ((void *) NULL);
}
