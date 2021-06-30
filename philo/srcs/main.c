/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukim <ukim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:39:59 by seapark           #+#    #+#             */
/*   Updated: 2021/06/30 13:40:34 by ukim             ###   ########.fr       */
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

int				main(int ac, char **av)
{
	t_arg			arg;
	t_philo			*p;

	if (check_arg(ac, av))
		return (0);
	arg = init_s_arg(ac, av);
	if (!(p = init_philo(&arg)))
		return (exit_error("e: Failed to initialize fork\n"));
	if (ft_atoi(av[1]) == 1)
		return (exit_error("e: philosopher should be > 1\n"));
	if (start_philosophers(p))
		return (exit_error("e: runtime error\n"));
	return (0);
}
