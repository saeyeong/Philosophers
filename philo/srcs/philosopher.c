/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 15:42:36 by ukim              #+#    #+#             */
/*   Updated: 2021/07/13 23:32:57 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void				think_philo(t_philo *p)
{
	print_state(p, STATE_THINK);
}

void				take_forks(t_philo *p)
{
	pthread_mutex_lock(p->lfork);
	pthread_mutex_lock(p->rfork);
	print_state(p, STATE_FORK);
}

void				eat_spaghetti(t_philo *p)
{
	long long		time;

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
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(p->rfork);
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
	if (p->philo_num % 2)
		usleep(15000);
	while (1)
	{
		if (p->info->limit_of_eat != -1 && \
		p->info->limit_of_eat <= p->eat_num)
		{
			p->info->death_philo_count++;
			print_state(p, STATE_EAT_ALL);
			break ;
		}
		take_forks(p);
		eat_spaghetti(p);
		sleep_philo(p);
		think_philo(p);
	}
	return ((void*)0);
}
