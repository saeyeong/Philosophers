/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:28:16 by ukim              #+#    #+#             */
/*   Updated: 2021/06/30 16:20:07 by ukim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int					exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

void				init_philoo(t_philo *p, pthread_t *monitor,\
pthread_mutex_t **prin_fork_chdie, int i)
{
	p->how_many_eat = 0;
	p->philo_num = i + 1;
	p->print_m = prin_fork_chdie[0];
	p->check_died = prin_fork_chdie[2];
	p->monitor = monitor;
	p->lfork = &(prin_fork_chdie[1][i]);
}
