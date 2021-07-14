/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:39:59 by ukim              #+#    #+#             */
/*   Updated: 2021/07/14 23:38:29 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void				*monitoring_all_child_exit(void *philo)
{
	t_philo			*p;
	int				i;
	int				status;

	p = (t_philo *)philo;
	usleep(p->info->time_to_die * 1000);
	i = 0;
	while (i < p->info->num_philo)
	{
		waitpid(p[i].pid, &status, 0);
		i++;
	}
	sem_post(p->info->check_die);
	return ((void*)0);
}

void				*monitoring_philo_died(void *philo)
{
	t_philo			*p;
	long long		last_meal_ms;
	struct timeval	time_now;

	p = (t_philo *)philo;
	usleep(p->info->time_to_die * 1000);
	while (1)
	{
		usleep(50);
		last_meal_ms = change_to_ms(p->last_meal);
		gettimeofday(&time_now, NULL);
		if (last_meal_ms + p->info->time_to_die < change_to_ms(time_now))
		{
			print_state(p, STATE_DIED);
			sem_post(p->info->check_die);
			return ((void*)0);
		}
	}
	return ((void*)0);
}
