/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:39:59 by ukim              #+#    #+#             */
/*   Updated: 2021/07/13 22:06:12 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int				check_arg(int ac, char **av)
{
	int	i;
	int j;

	if (!(ac == 5 || ac == 6))
		return (exit_error("e: bad arguments\n"));
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (exit_error("e: bad arguments\n"));
			j++;
		}
		i++;
	}
	return (0);
}

void				*monitoring(void *philo)
{
	t_philo			*p;
	int				i;
	long long		last_meal_ms;
	struct timeval	time_now;

	p = (t_philo *)philo;
	usleep(p->info->time_to_die * 1000);
	while (1)
	{
		i = -1;
		usleep(50);
		while (++i < p->info->number_of_philosophers)
		{
			last_meal_ms = change_to_ms(p[i].last_meal);
			gettimeofday(&time_now, NULL);
			if (last_meal_ms + p->info->time_to_die < change_to_ms(time_now))
			{
				if (p->info->death_philo_count != p->info->number_of_philosophers)
					print_state(&p[i], STATE_DIED);
				pthread_mutex_unlock(p->info->check_died);
				return ((void*)0);
			}
		}
	}
	return ((void*)0);
}

int					start_pthread(t_philo *p)
{
	int				i;

	i = 0;
	while (i < p->info->number_of_philosophers)
	{
		if (pthread_create(&(p[i].pthread), NULL, \
		&sit_at_a_round_table, (void *)&(p[i])) != 0)
			return (1);
		pthread_detach(p[i].pthread);
		i++;
	}
	if (pthread_create(p->info->monitor, NULL, &monitoring, (void *)p) != 0)
		return (1);
	pthread_detach(*p->info->monitor);
	pthread_mutex_lock(p->info->check_died);
	pthread_mutex_unlock(p->info->check_died);
	return (0);
}

int				main(int ac, char **av)
{
	t_common_info	*info;
	t_philo			*p;

	if (check_arg(ac, av))
		return (0);
	if (!(info = init_common_info(ac, av)))
		return (exit_error("e: Failed to initialize info\n"));
	if (!(p = init_philo(info)))
		return (exit_error("e: Failed to initialize philo\n"));
	if (start_pthread(p))
		return (exit_error("e: runtime error\n"));
	return (0);
}
