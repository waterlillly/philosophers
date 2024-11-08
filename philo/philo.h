/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:56:13 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/11/08 16:28:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <error.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2
# define FORK 3

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		px;
	pthread_t			ptid;
	int					fork_r;
	int					fork_l;
	long				mc;
	long				last_meal;
	bool				done;
	t_sim				*sim;
}						t_philo;

typedef struct s_sim
{
	pthread_mutex_t		*forkx;
	pthread_mutex_t		stopx;
	bool				stop;
	long				start;
	int					nop;
	long				ttd;
	long				tte;
	long				tts;
	long				mte;
	pthread_mutex_t		write_x;
	pthread_t			monitor;
}						t_sim;

/*UTILS-FOLDER*/
long					ft_atoi_long(const char *nptr);
char					*ft_itoa_long(long n);
void					ft_putendl_fd(char *s, int fd);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
bool					ft_strcmp_bool(const char *s1, const char *s2);
char					*ft_strdup(const char *s);
size_t					ft_strlen(const char *s);
char					*ft_strjoin(char const *s1, char const *s2);
int						exit_gracefully_no_threads(t_sim *sim, t_philo *p,
							int i, const char *err);
int						exit_gracefully(t_sim *sim, t_philo *p, int i,
							const char *err);
void					write_x_smth(t_sim *sim, char *s);
long					get_time(void);
void					ft_usleep(long time, t_sim *sim);
void					death(t_philo *p);
int						free_and_destroy_mutexes(t_philo *p);
int						join_threads(t_philo *p);
int						err_ex(const char *err, t_philo *p, t_sim *sim);
long					cur_time(t_philo *p);
void					print_state(int state, t_sim *sim, t_philo *p);
void					start_routine(t_philo *p);
int						create_x(t_sim *sim, t_philo *p);
int						create_forks(t_sim *sim, t_philo *p);
void					*monitoring(void *arg);
int						create_monitor(t_sim *sim, t_philo *p);
void					*routine(void *arg);
int						init_philos(t_philo *p, t_sim *sim);
int						create_philos(t_sim *sim, t_philo *p);
bool					is_dead(t_philo *p);
t_philo					*init_input(t_sim *sim, int ac, char **av);
bool					ft_check_arg(int ac, char **in);
bool					check_args(int ac, char **av);
int						main(int ac, char **av);

#endif