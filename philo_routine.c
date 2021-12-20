/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:28:24 by zsidki            #+#    #+#             */
/*   Updated: 2021/12/20 17:24:35 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_main *i)
{
	i->last_time_eat = get_time_stamp() / 1000;
	pthread_mutex_lock(i->m_died);
	printf("%ld %d is eating\n", i->last_time_eat, i->id + 1);
	pthread_mutex_unlock(i->m_died);
	ft_usleep(i->args->time_to_eat * 1000);
}

void	p_sleep(t_main *i)
{
	pthread_mutex_lock(i->m_died);
	printf("%ld %d is sleeping\n", get_time_stamp() / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
	ft_usleep(i->args->time_to_sleep * 1000);
}

void	p_think(t_main *i)
{
	pthread_mutex_lock(i->m_died);
	printf("%ld %d is thinking\n", get_time_stamp() / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
}

void	p_takefork(t_main *i)
{
	pthread_mutex_lock(i->m_died);
	printf("%ld %d has taken a fork\n", get_time_stamp() / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
}

void	*routine(void *arg)
{
	t_main	*main;

	main = (t_main *)arg;
	while (1)
	{
		p_think(main);
		pthread_mutex_lock(&main->mutex[main->id]);
		p_takefork(main);
		pthread_mutex_lock(&main->mutex[(main->id + 1)
			% main->args->nb_of_philo]);
		p_takefork(main);
		p_eat(main);
		pthread_mutex_unlock(&main->mutex[main->id]);
		pthread_mutex_unlock(&main->mutex[(main->id + 1)
			% main->args->nb_of_philo]);
		if (main->args->nb_must_eat != -1)
			main->nb_eat++;
		if (main->args->nb_must_eat == main->nb_eat)
			break ;
		p_sleep(main);
	}
	return (0);
}
