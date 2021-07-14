/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 15:42:36 by seapark           #+#    #+#             */
/*   Updated: 2021/07/15 00:02:40 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void				think_philo(t_philo *p)
{
	print_state(p, STATE_THINK);
}

void				take_forks(t_philo *p)
{
	sem_wait(p->info->forks);
	sem_wait(p->info->forks);
	print_state(p, STATE_FORK);
}

void				eat_spaghetti(t_philo *p)
{
	long long	time;

	time = now_time();
	print_state(p, STATE_EAT);
	if (p->info->limit_of_eat != -1)
		p->eat_num += 1;
	while (1)
	{
		if (calculate_time(time, now_time()) >= p->info->time_to_eat)
			break ;
		usleep(50);
	}
	gettimeofday(&p->last_meal, NULL);
}

void				sleep_philo(t_philo *p)
{
	long long		time;

	time = now_time();
	sem_post(p->info->forks);
	sem_post(p->info->forks);
	print_state(p, STATE_SLEEP);
	while (1)
	{
		if (calculate_time(time, now_time()) >= p->info->time_to_sleep)
			break ;
		usleep(50);
	}
}

void				*sit_at_a_round_table(void *philo)
{
	t_philo			*p;

	p = (t_philo *)philo;
	init_created_philo(p);
	if (pthread_create(p->info->child_monitor, NULL, \
	&monitoring_philo_died, (void *)p) != 0)
		return ((void*)0);
	pthread_detach(*p->info->child_monitor);
	if (p->philo_num % 2)
		usleep(15000);
	while (1)
	{
		take_forks(p);
		eat_spaghetti(p);
		sleep_philo(p);
		think_philo(p);
		if (p->info->limit_of_eat != -1 && \
		p->info->limit_of_eat <= p->eat_num)
		{
			print_state(p, STATE_EAT_ALL);
			break ;
		}
	}
	return ((void*)0);
}
