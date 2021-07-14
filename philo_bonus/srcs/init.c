/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:13:21 by ukim              #+#    #+#             */
/*   Updated: 2021/07/14 23:33:51 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

sem_t				*init_forks(int num_phi)
{
	sem_t			*forks;

	sem_unlink("forks");
	if ((forks = sem_open("forks", O_CREAT, 0777, num_phi)) == SEM_FAILED)
	{
		free(forks);
		return (NULL);
	}
	return (forks);
}

t_common_info		*init_sem(t_common_info *info)
{
	sem_unlink("print");
	if ((info->print_s = sem_open("print", O_CREAT, 0777, 1)) == SEM_FAILED)
	{
		free(info->print_s);
		return (NULL);
	}
	sem_unlink("check_die");
	if ((info->check_die = \
	sem_open("check_die", O_CREAT, 0777, 0)) == SEM_FAILED)
	{
		free(info->check_die);
		return (NULL);
	}
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
	if (!(info->print_s = (sem_t*)malloc(sizeof(sem_t))))
		return (NULL);
	if (!(info->child_monitor = (pthread_t *)malloc(sizeof(pthread_t))))
		return (NULL);
	if (!(info->main_monitor = (pthread_t *)malloc(sizeof(pthread_t))))
		return (NULL);
	if (!(init_sem(info)))
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
	sem_t			*forks;
	int				i;

	if (!(philo = (t_philo *)malloc(sizeof(t_philo) * \
	info->number_of_philosophers)))
		return (NULL);
	if (!(forks = init_forks(info->number_of_philosophers)))
		return (NULL);
	i = 0;
	info->forks = forks;
	while (i < info->number_of_philosophers)
	{
		philo[i].eat_num = 0;
		philo[i].philo_num = i + 1;
		philo[i].info = info;
		i++;
	}
	return (philo);
}
