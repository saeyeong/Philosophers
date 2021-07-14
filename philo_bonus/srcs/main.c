/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:39:59 by ukim              #+#    #+#             */
/*   Updated: 2021/07/14 23:39:09 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int					check_arg(int ac, char **av)
{
	int				i;
	int				j;

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

void				kill_all_process(t_philo *p)
{
	int				i;

	i = 0;
	while (i < p->info->num_philo)
	{
		kill(p[i].pid, SIGINT);
		i++;
	}
}

int					start_process(t_philo *p)
{
	int				i;

	i = 0;
	while (i < p->info->num_philo)
	{
		p[i].pid = fork();
		if (p[i].pid == 0)
		{
			sit_at_a_round_table(&p[i]);
			exit(0);
		}
		i++;
	}
	if (pthread_create(p->info->main_monitor, NULL, \
	&monitoring_all_child_exit, (void *)p) != 0)
		return (1);
	pthread_detach(*p->info->main_monitor);
	sem_wait(p->info->check_die);
	kill_all_process(p);
	return (0);
}

int					main(int ac, char **av)
{
	t_common_info	*info;
	t_philo			*p;

	if (check_arg(ac, av))
		return (0);
	if (!(info = init_common_info(ac, av)))
		return (exit_error("e: Failed to initialize info\n"));
	if (!(p = init_philo(info)))
		return (exit_error("e: Failed to initialize philo\n"));
	if (start_process(p))
		return (exit_error("e: runtime error\n"));
	return (0);
}
