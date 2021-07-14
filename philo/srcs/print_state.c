/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 15:07:27 by seapark           #+#    #+#             */
/*   Updated: 2021/07/15 00:02:40 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long				calculate_time(long long past, long long now)
{
	return (now - past);
}

long long				now_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long long				change_to_ms(struct timeval tv)
{
	long long				current_us;

	current_us = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_us);
}

void					print_state(t_philo *p, int state)
{
	long long			created_ms;
	long long			current_ms;
	long long			timestamp_ms;

	created_ms = p->created;
	current_ms = now_time();
	timestamp_ms = current_ms - created_ms;
	pthread_mutex_lock(p->info->print_m);
	if (state == STATE_FORK)
		printf("%llu %d has taken a fork\n", timestamp_ms, p->philo_num);
	else if (state == STATE_EAT)
		printf("%llu %d is eating\n", timestamp_ms, p->philo_num);
	else if (state == STATE_SLEEP)
		printf("%llu %d is sleeping\n", timestamp_ms, p->philo_num);
	else if (state == STATE_THINK)
		printf("%llu %d is thinking\n", timestamp_ms, p->philo_num);
	else if (state == STATE_EAT_ALL)
		printf("%llu %d died with happy\n", timestamp_ms, p->philo_num);
	else if (state == STATE_DIED)
	{
		printf("%llu %d died\n", timestamp_ms, p->philo_num);
		return ;
	}
	pthread_mutex_unlock(p->info->print_m);
}
