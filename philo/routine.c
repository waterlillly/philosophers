/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:20:01 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/08 17:10:44 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *p)
{
	pthread_mutex_lock(&p->sim->stopx);
	if (p->sim->stop == false)
	{
		pthread_mutex_unlock(&p->sim->stopx);
		return (false);
	}
	pthread_mutex_unlock(&p->sim->stopx);
	return (true);
}

static void	single_routine(t_philo *p)
{
	pthread_mutex_lock(&p->sim->forkx[p->fork_r]);
	print_state(FORK, p->sim, p);
	ft_usleep(p->sim->ttd, p->sim);
	pthread_mutex_unlock(&p->sim->forkx[p->fork_r]);
}

static bool	eating_routine(t_philo *p)
{
	pthread_mutex_lock(&p->sim->forkx[p->fork_r]);
	print_state(FORK, p->sim, p);
	pthread_mutex_lock(&p->sim->forkx[p->fork_l]);
	print_state(FORK, p->sim, p);
	pthread_mutex_lock(&p->px);
	p->last_meal = cur_time(p);
	pthread_mutex_unlock(&p->px);
	if (!is_dead(p))
	{
		print_state(EATING, p->sim, p);
		pthread_mutex_lock(&p->px);
		p->mc++;
		if (p->sim->mte > 0 && p->mc >= p->sim->mte)
			p->done = true;
		pthread_mutex_unlock(&p->px);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&p->sim->forkx[p->fork_r]);
		pthread_mutex_unlock(&p->sim->forkx[p->fork_l]);
		return (false);
	}
}

void	start_routine(t_philo *p)
{
	if (p->sim->nop == 1)
		return (single_routine(p));
	while (!is_dead(p))
	{
		if (!eating_routine(p))
			break ;
		ft_usleep(p->sim->tte, p->sim);
		pthread_mutex_unlock(&p->sim->forkx[p->fork_r]);
		pthread_mutex_unlock(&p->sim->forkx[p->fork_l]);
		ft_usleep(1, p->sim);
		if (!is_dead(p))
		{
			print_state(SLEEPING, p->sim, p);
			ft_usleep(p->sim->tts, p->sim);
		}
		if (!is_dead(p))
			print_state(THINKING, p->sim, p);
	}
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (!p)
		err_ex("no philos present", p, p->sim);
	if (p->sim->nop % 2 != 0)
	{
		if (p->sim->nop > 1 && p->id % 2 != 0)
			ft_usleep(30, p->sim);
	}
	else
	{
		if (p->id % 2 == 0)
			ft_usleep(30, p->sim);
	}
	start_routine(p);
	return ((void *) NULL);
}
