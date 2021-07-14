/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:40:42 by ukim              #+#    #+#             */
/*   Updated: 2021/07/14 15:38:52 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

# define STATE_FORK		0
# define STATE_EAT		1
# define STATE_SLEEP	2
# define STATE_THINK	3
# define STATE_DIED		4
# define STATE_EAT_ALL	5

typedef struct			s_common_info
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					limit_of_eat;
	sem_t				*print_s;
	sem_t				*forks;
	pthread_t			*child_monitor;
	pthread_t			*main_monitor;
	sem_t				*check_die;
}						t_common_info;

typedef struct			s_philo
{
	int					eat_num;
	int					philo_num;
	long long			created;
	struct timeval		last_meal;
	t_common_info		*info;
	pid_t				pid;
}						t_philo;

int						ft_atoi(const char *s);
int						ft_strlen(const char *s);
int						ft_isdigit(int c);
int						exit_error(char const *str);
t_common_info			*init_common_info(int ac, char **av);
sem_t					*init_forks(int number_of_philosophers);
void					init_created_philo(t_philo *p);
t_common_info			*init_sem(t_common_info *info);
void					*monitoring_philo_died(void *p);
void					*monitoring_all_child_exit(void *p);
int						start_process(t_philo *p);
void					*sit_at_a_round_table(void *philo);
void					print_state(t_philo *p, int state);
long long				change_to_ms(struct timeval tv);
void					take_forks(t_philo *p);
void					eat_spaghetti(t_philo *p);
void					sleep_philo(t_philo *p);
void					think_philo(t_philo *p);
t_philo					*init_philo(t_common_info *common_info);
long long				now_time(void);
long long				calculate_time(long long past, long long now);
void					think_philo(t_philo *p);
#endif
