/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:16:54 by lbaumeis          #+#    #+#             */
/*   Updated: 2025/02/03 13:58:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	cur_time(t_philo *p)
{
	long	cur_time;

	cur_time = get_time() - p->sim->start;
	if (cur_time < 0)
		err_ex("time failed", p, p->sim);
	return (cur_time);
}

long	get_time(void)
{
	long			now;
	struct timeval	tv;

	now = 0;
	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	now = ((tv.tv_sec) * 1000 + tv.tv_usec / 1000);
	return (now);
}

void	ft_usleep(long time, t_sim *sim)
{
	long	start;
	long	end;

	start = get_time();
	if (start < 0)
		err_ex("time error", NULL, sim);
	end = start + time;
	while (get_time() < end)
	{
		pthread_mutex_lock(&sim->stopx);
		if (sim->stop == false)
		{
			pthread_mutex_unlock(&sim->stopx);
			usleep(10);
		}
		else
		{
			pthread_mutex_unlock(&sim->stopx);
			break ;
		}
	}
}
