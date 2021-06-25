/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:13:21 by seapark           #+#    #+#             */
/*   Updated: 2021/06/25 16:39:49 by seapark          ###   ########.fr       */
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

void			*test1(void *philo)
{
	t_philo			*p;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	struct timeval	time_s;
	long int		time;
	long int		created;

	p = (t_philo *)philo;
	lfork = (*p).lfork;
	rfork = (*p).rfork;

	gettimeofday(&(*p).created, NULL);
	created = (long int)(*p).created.tv_sec * (long int)1000000 + (long int)(*p).created.tv_usec;


    pthread_mutex_lock(lfork);
    pthread_mutex_lock(rfork);
	
	
	gettimeofday(&time_s, NULL);
	time = (long int)time_s.tv_sec * (long int)1000000 + (long int)time_s.tv_usec;

	printf("철학자%d : 냠이%ld\n", (*p).philo_num, time - created);

    pthread_mutex_unlock(lfork);
    pthread_mutex_unlock(rfork);
	return ((void*)0);
}

t_philo_time		set_philo_time(char **av)
{
	t_philo_time philo_time;

	philo_time.time_to_die = ft_atoi(av[2]);
	philo_time.time_to_eat = ft_atoi(av[3]);
	philo_time.time_to_sleep = ft_atoi(av[4]);
	return (philo_time);
}

int		start_philosophers(int number_of_philosophers, pthread_mutex_t *forks)
{
	t_philo			*philo;
	int				i;
    int				status;
	
	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo *) * number_of_philosophers);
	while (i < number_of_philosophers)
	{
		philo[i].philo_num = i;
		philo[i].lfork = &forks[i];
		philo[i].rfork = &forks[(i + 1) % number_of_philosophers];
		if (pthread_create(&philo[i].pthread, NULL, &test1, (void *)&philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_join(philo[i].pthread, (void **)&status);
		i++;
	}
	return (0);
}