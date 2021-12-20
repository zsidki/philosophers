/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:24:06 by zsidki            #+#    #+#             */
/*   Updated: 2021/12/20 17:18:39 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*creat_forks(t_args args)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * args.nb_of_philo);
	while (i < args.nb_of_philo)
	{
		pthread_mutex_init(mutex + i, NULL);
		i++;
	}
	return (mutex);
}

t_main	*creat_philos(t_args args, pthread_mutex_t *mutex)
{
	t_main			*philos;
	pthread_mutex_t	m_died;
	int				i;
	long			t;

	pthread_mutex_init(&m_died, NULL);
	philos = malloc(sizeof(t_main) * args.nb_of_philo);
	philos->threads = malloc(sizeof(pthread_t) * args.nb_of_philo);
	t = get_time_stamp() / 1000;
	i = 0;
	while (i < args.nb_of_philo)
	{
		philos[i].id = i;
		philos[i].args = &args;
		philos[i].mutex = mutex;
		philos[i].nb_eat = 0;
		philos[i].m_died = &m_died;
		philos[i].last_time_eat = t;
		if (pthread_create(philos->threads + i, NULL,
				&routine, &philos[i]) != 0)
			write(2, "Faild to creat thread\n", 22);
		usleep(100);
		i++;
	}
	return (philos);
}

int	supervisor(t_args args, t_main *philos)
{
	int		finish_eat;
	int		i;
	long	t;

	finish_eat = 0;
	while (finish_eat != args.nb_of_philo)
	{
		finish_eat = 0;
		i = -1;
		while (++i < args.nb_of_philo)
		{
			t = get_time_stamp() / 1000;
			if (philos[i].nb_eat == args.nb_must_eat)
				finish_eat++;
			else if (t - philos[i].last_time_eat >= args.time_to_die)
			{
				pthread_mutex_lock(philos[i].m_died);
				if (t - philos[i].last_time_eat >= args.time_to_die)
					return (printf("%ld %d Died\n", t, philos[i].id + 1));
				else
					pthread_mutex_unlock(philos[i].m_died);
			}
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args			args;
	t_main			*philos;
	pthread_mutex_t	*mutex;

	if (init_args(&args, argc, argv))
		return (1);
	mutex = creat_forks(args);
	philos = creat_philos(args, mutex);
	supervisor(args, philos);
	free(philos->threads);
	free(mutex);
	free(philos);
	return (0);
}
