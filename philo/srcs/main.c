/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seapark <seapark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 16:39:59 by seapark           #+#    #+#             */
/*   Updated: 2021/06/25 15:07:58 by seapark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int				check_arg(int ac, char **av)
{
	int	i;
	int j;
	
	if (ac != 5)
		return (exit_error("e: bad arguments\n"));
	i = 1;
	while (av[i])
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
	int				number_of_philosophers;
	t_philo_time	philo_time;
	pthread_mutex_t	*forks;

	if (check_arg(ac, av))
		return (0);
	number_of_philosophers = ft_atoi(av[1]);
	philo_time = set_philo_time(av);
	if (!(forks = init_forks(number_of_philosophers)))
		return (exit_error("e: Failed to initialize fork\n"));
	if (start_philosophers(number_of_philosophers, forks))
		return (exit_error("e: runtime error\n"));
	return (0);
}
