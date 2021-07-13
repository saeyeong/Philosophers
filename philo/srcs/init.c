/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:13:21 by ukim              #+#    #+#             */
/*   Updated: 2021/07/13 20:20:12 by ukim             ###   ########.fr       */
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

t_common_info		*init_common_mutex(t_common_info *info)
{
	if (!(info->print_m = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (NULL);
	if (!(info->monitor = (pthread_t *)malloc(sizeof(pthread_t))))
		return (NULL);
	if (!(info->check_died = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (NULL);
	if (pthread_mutex_init(info->print_m, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(info->check_died, NULL) != 0)
		return (NULL);
	pthread_mutex_lock(info->check_died);
	return (info);
}

t_common_info		*init_common_info(int ac, char **av)
{
	t_common_info	*info;

	if (!(info = (t_common_info*)malloc(sizeof(t_common_info))))
		return (NULL);
	info->number_of_philosophers = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->limit_of_eat = ft_atoi(av[5]);
	else
		info->limit_of_eat = -1;
	info->death_philo_count = 0;
	if (!(init_common_mutex(info)))
		return (NULL);
	return (info);
}

void				init_created_philo(t_philo *p)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	p->created = change_to_ms(tv);
}

t_philo				*init_philo(t_common_info *info)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				i;

	if (!(philo = (t_philo *)malloc(sizeof(t_philo) * info->number_of_philosophers)))
		return (NULL);
	if (!(forks = init_forks(info->number_of_philosophers)))
		return (NULL);
	i = 0;
	while (i < info->number_of_philosophers)
	{
		philo[i].rfork = &forks[(i + 1) % info->number_of_philosophers];
		philo[i].lfork = &forks[i];
		philo[i].eat_num = 0;
		philo[i].philo_num = i + 1;
		philo[i].info = info;
		i++;
	}
	return (philo);
}
