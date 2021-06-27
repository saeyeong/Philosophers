/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:13:21 by seapark           #+#    #+#             */
/*   Updated: 2021/06/27 21:49:58 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t		*init_forks(int number_of_philosophers)
{
	pthread_mutex_t	*forks;
	int				i;

	if (!(forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * number_of_philosophers)))
		return (NULL);
	i = 0;
	while (i < number_of_philosophers)
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

t_arg				init_s_arg(char **av)
{
	t_arg 			arg;

	arg.number_of_philosophers = ft_atoi(av[1]);
	arg.time_to_die = ft_atoi(av[2]);
	arg.time_to_eat = ft_atoi(av[3]);
	arg.time_to_sleep = ft_atoi(av[4]);
	return (arg);
}

void				init_created_philo(t_philo *p)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	// printf("%lu.%d\n",tv.tv_sec,tv.tv_usec);
	p->created = change_to_ms(tv);
	// printf("%llu\n",p->created);
}

t_philo				*init_philo(t_arg *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*check_died;
	pthread_mutex_t	*print_m;
	int				i;
	pthread_t		*monitor;
	pthread_mutex_t	*forks;

	philo = (t_philo *)malloc(sizeof(t_philo) * arg->number_of_philosophers);
	monitor = (pthread_t *)malloc(sizeof(pthread_t));
	check_died = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	print_m = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));	
	if (!(forks = init_forks(arg->number_of_philosophers)))
		return (NULL);
	if (pthread_mutex_init(print_m, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(check_died, NULL) != 0)
		return (NULL);
	pthread_mutex_lock(check_died);
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		philo[i].philo_num = i + 1;
		philo[i].print_m = print_m;
		philo[i].check_died = check_died;
		philo[i].monitor = monitor;
		philo[i].arg = arg;
		philo[i].lfork = &(forks[i]);
		philo[i].rfork = &(forks[(i + 1) % arg->number_of_philosophers]);
		i++;
	}
	return (philo);
}

int					start_philosophers(t_philo *p)
{
	int				i;
	int				status;
	
	i = 0;
	status = 0;
	while (i < p->arg->number_of_philosophers)
	{
		if (pthread_create(&p[i].pthread, NULL, &sit_at_a_round_table, (void *)&p[i]) != 0)
			return (1);
		pthread_detach(p[i].pthread);
		i++;
	}
	if (pthread_create(p->monitor, NULL, &monitoring, (void *)p) != 0)
		return (1);
	// pthread_join(*p->monitor, (void **)&status);
	// usleep(1000);
	// pthread_mutex_lock(p->check_died);
	pthread_mutex_lock(p->check_died);
	pthread_mutex_unlock(p->check_died);
	return (0);
}