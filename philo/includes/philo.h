/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:40:42 by ukim              #+#    #+#             */
/*   Updated: 2021/06/30 16:20:42 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# define STATE_FORK		0
# define STATE_EAT		1
# define STATE_SLEEP	2
# define STATE_THINK	3
# define STATE_DIED		4
# define STATE_EAT_ALL	5

typedef struct			s_arg
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					limit_of_eat;
	int					death_philo_count;
}						t_arg;

typedef struct			s_philo
{
	int					how_many_eat;
	int					philo_num;
	t_arg				*arg;
	long long			created;
	struct timeval		last_meal;
	pthread_t			pthread;
	pthread_t			*monitor;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		*check_died;
	pthread_mutex_t		*print_m;
}						t_philo;

int						ft_atoi(const char *s);
int						ft_strlen(const char *s);
int						ft_isdigit(int c);
int						exit_error(char const *str);
t_arg					init_s_arg(int ac, char **av);
pthread_mutex_t			*init_forks(int number_of_philosophers);
void					init_created_philo(t_philo *p);
int						start_philosophers();
void					*sit_at_a_round_table(void *philo);
void					print_state(t_philo *p, int state);
long long				change_to_ms(struct timeval tv);
void					take_forks(t_philo *p);
void					eat_spaghetti(t_philo *p);
void					sleep_philo(t_philo *p);
void					think_philo(t_philo *p);
void					*monitoring(void *p);
t_philo					*init_philo(t_arg *arg);
long long				now_time(void);
long long				calculate_time(long long past, long long now);
void					think_philo(t_philo *p);
void					init_philoo(t_philo *p, pthread_t *monitor,\
pthread_mutex_t **prin_fork_chdie, int i);
#endif
