/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 15:42:36 by seapark           #+#    #+#             */
/*   Updated: 2021/06/27 21:56:28 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void				take_forks(t_philo *p)
{
	pthread_mutex_lock(p->lfork);
	pthread_mutex_lock(p->rfork);
	print_state(p, STATE_FORK);
}

void				eat_spaghetti(t_philo *p)
{
	print_state(p, STATE_EAT);
	gettimeofday(&p->last_meal, NULL);
	usleep(p->arg->time_to_eat * 1000);
}

void				sleep_philo(t_philo *p)
{
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(p->rfork);
	print_state(p, STATE_SLEEP);
	usleep(p->arg->time_to_sleep * 1000);
}

void				think_philo(t_philo *p)
{
	print_state(p, STATE_THINK);
}

void				*monitoring(void *philo)
{
	t_philo			*p;
	int 			i;
	long long		last_meal_ms;
	long long		time_to_die;
	struct timeval	time_now;
	
	p = (t_philo *)philo;
	time_to_die = p->arg->time_to_die;
	usleep(time_to_die*1000);
	while (1)
	{
		i = 0;
		while (p[i].philo_num)
		{
			last_meal_ms = change_to_ms(p[i].last_meal);
			gettimeofday(&time_now, NULL);
			if (last_meal_ms + time_to_die < change_to_ms(time_now))
			{
				print_state(&p[i], STATE_DIED);
				pthread_mutex_lock(p->print_m);
				pthread_mutex_unlock(p->check_died);
				return ((void*)0);
			}
			i++;
		}
	}
	return ((void*)0);
}

void				*sit_at_a_round_table(void *philo)
{
	t_philo			*p;

	p = (t_philo *)philo;
	init_created_philo(p);
	while (1)
	{
		take_forks(p);
		eat_spaghetti(p);
		sleep_philo(p);
		think_philo(p);
	}
	return ((void*)0);
}