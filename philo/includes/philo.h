/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:40:42 by seapark           #+#    #+#             */
/*   Updated: 2021/07/15 00:02:40 by seapark          ###   ########.fr       */
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

typedef struct			s_common_info
{
	int					num_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					limit_of_eat;
	int					death_philo_count;
	pthread_mutex_t		*check_died;
	pthread_mutex_t		*print_m;
	pthread_t			*monitor;
}						t_common_info;

typedef struct			s_philo
{
	int					eat_num;
	int					philo_num;
	long long			created;
	struct timeval		last_meal;
	pthread_t			pthread;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	t_common_info		*info;
}						t_philo;

int						ft_atoi(const char *s);
int						ft_strlen(const char *s);
int						ft_isdigit(int c);
int						exit_error(char const *str);
t_common_info			*init_common_mutex(t_common_info *info);
t_common_info			*init_common_info(int ac, char **av);
pthread_mutex_t			*init_forks(int num_philo);
void					init_created_philo(t_philo *p);
int						start_pthread(t_philo *p);
void					*sit_at_a_round_table(void *philo);
void					print_state(t_philo *p, int state);
long long				change_to_ms(struct timeval tv);
void					take_forks(t_philo *p);
void					eat_spaghetti(t_philo *p);
void					sleep_philo(t_philo *p);
void					think_philo(t_philo *p);
void					*monitoring(void *p);
t_philo					*init_philo(t_common_info *common_info);
long long				now_time(void);
long long				calculate_time(long long past, long long now);
void					think_philo(t_philo *p);
#endif
