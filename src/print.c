/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:17:35 by lbaumeis          #+#    #+#             */
/*   Updated: 2025/02/03 13:58:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_state(int state, t_sim *sim, t_philo *p)
{
	pthread_mutex_lock(&p->px);
	pthread_mutex_lock(&sim->write_x);
	if (!is_dead(p) && state == 0)
		printf("\033[0;33m%ld %d is eating\033[0m\n", p->last_meal, p->id + 1);
	else if (!is_dead(p) && state == 1)
		printf("\033[0;34m%ld %d is sleeping\033[0m\n", cur_time(p), p->id + 1);
	else if (!is_dead(p) && state == 2)
		printf("\033[0;32m%ld %d is thinking\033[0m\n", cur_time(p), p->id + 1);
	else if (!is_dead(p) && state == 3)
		printf("%ld %d has taken a fork\n", cur_time(p), p->id + 1);
	pthread_mutex_unlock(&sim->write_x);
	pthread_mutex_unlock(&p->px);
}

void	write_x_smth(t_sim *sim, char *s)
{
	pthread_mutex_lock(&sim->write_x);
	printf("\033[0;31m%s\033[0m\n", s);
	pthread_mutex_unlock(&sim->write_x);
}
