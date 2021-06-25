/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:40:42 by seapark           #+#    #+#             */
/*   Updated: 2021/06/25 16:25:58 by seapark          ###   ########.fr       */
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

typedef struct			s_philo
{
	int 				philo_num;
	struct timeval		created;
	pthread_t			pthread;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
}						t_philo;

typedef struct			s_philo_time
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}						t_philo_time;

int						ft_atoi(const char *s);
int						ft_strlen(const char *s);
int						ft_isdigit(int c);
int						exit_error(char const *str);
t_philo_time			set_philo_time(char **av);
int						start_philosophers(int number_of_philosophers, pthread_mutex_t *forks);
pthread_mutex_t			*init_forks(int number_of_philosophers);

#endif
