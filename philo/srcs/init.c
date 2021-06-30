/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:13:21 by seapark           #+#    #+#             */
/*   Updated: 2021/06/30 14:30:34 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t		*init_forks(int num_phi)
{
	pthread_mutex_t	*forks;
	int				i;

	if (!(forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * num_phi)))
		return (NULL);
	i = 0;
	while (i < num_phi)
	{
		if (pthread_mutex_init(&forks[i], NULL) < 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_arg				init_s_arg(int ac, char **av)
{
	t_arg			arg;

	arg.number_of_philosophers = ft_atoi(av[1]);
	arg.time_to_die = ft_atoi(av[2]);
	arg.time_to_eat = ft_atoi(av[3]);
	arg.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg.limit_of_eat = ft_atoi(av[5]);
	else
		arg.limit_of_eat = -1;
	arg.death_philo_count = 0;
	return (arg);
}

void				init_created_philo(t_philo *p)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	p->created = change_to_ms(tv);
}

t_philo				*init_philo(t_arg *arg)
{
	int				i;
	t_philo			*philo;
	pthread_t		*monitor;
	pthread_mutex_t	*prin_fork_chdie[3];

	philo = (t_philo *)malloc(sizeof(t_philo) * arg->number_of_philosophers);
	monitor = (pthread_t *)malloc(sizeof(pthread_t));
	prin_fork_chdie[2] = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	prin_fork_chdie[0] = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	if (!(prin_fork_chdie[1] = init_forks(arg->number_of_philosophers)))
		return (NULL);
	if (pthread_mutex_init(prin_fork_chdie[0], NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(prin_fork_chdie[2], NULL) != 0)
		return (NULL);
	pthread_mutex_lock(prin_fork_chdie[2]);
	i = -1;
	while (++i < arg->number_of_philosophers)
	{
		philo[i].arg = arg;
		philo[i].rfork = &(prin_fork_chdie[1][(i + 1) \
		% arg->number_of_philosophers]);
		init_philoo(&philo[i], monitor, prin_fork_chdie, i);
	}
	return (philo);
}

int					start_philosophers(t_philo *p)
{
	int				i;
	int				status;
	struct timeval	tv;

	i = 0;
	status = 0;
	while (i < p->arg->number_of_philosophers)
	{
		if (pthread_create(&p[i].pthread, NULL, \
		&sit_at_a_round_table, (void *)&p[i]) != 0)
			return (1);
		gettimeofday(&tv, NULL);
		p[i].created = change_to_ms(tv);
		i++;
	}
	if (pthread_create(p->monitor, NULL, &monitoring, (void *)p) != 0)
		return (1);
	pthread_detach(*p->monitor);
	pthread_mutex_lock(p->check_died);
	pthread_mutex_unlock(p->check_died);
	return (0);
}
