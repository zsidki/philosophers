/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:32:22 by zsidki            #+#    #+#             */
/*   Updated: 2021/12/19 15:44:48 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	get_time_stamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (long)1000000 + tv.tv_usec);
}

void	ft_usleep(useconds_t usec)
{
	long	time;

	time = get_time_stamp();
	usleep(usec - 10 * 1000);
	while (get_time_stamp() < (time + usec));
}

void	init_args(struct args *args, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong number of arguments!\n", 27);
		exit(EXIT_FAILURE);
	}
	if (!check_arg(argv[argc - 1]))
	{
		write(2, "Wrong number offf arguments!\n", 27);
		exit(EXIT_FAILURE);
	}
	args->nb_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->nb_must_eat = -1;
	if (argc == 6)
	{
		args->nb_must_eat = ft_atoi(argv[5]);
	}
	if ((args->nb_must_eat < 0 && argc == 6) || args->nb_of_philo < 0
		|| args->time_to_die < 0 || args -> time_to_eat < 0 || args->time_to_sleep < 0)
	{
		write(2, "Invalid argument!\n", 18);
		exit(EXIT_FAILURE);
	}
}
