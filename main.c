/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:24:06 by zsidki            #+#    #+#             */
/*   Updated: 2021/12/18 18:17:26 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct args {
	int nb_of_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_must_eat;
};

typedef struct s_main
{
	int id;
	long last_time_eat;
	int nb_eat;
	struct args *args;
	pthread_mutex_t *mutex;
	pthread_mutex_t *m_died;
}				t_main;

long	get_time_stamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (long)1000000 + tv.tv_usec);
}

void ft_usleep(useconds_t usec) {
	long time = get_time_stamp();
	usleep(usec - 10*1000);
	while (get_time_stamp() < (time + usec));
}

void p_eat(t_main * i)
{
	i->last_time_eat = get_time_stamp() / 1000;
	pthread_mutex_lock(i->m_died);
    printf("%ld %d is eating\n", i->last_time_eat, i->id + 1);
	pthread_mutex_unlock(i->m_died);
	ft_usleep(i->args->time_to_eat * 1000);
}

void p_sleep(t_main * i)
{
	pthread_mutex_lock(i->m_died);
    printf("%ld %d is sleeping\n", get_time_stamp() / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
	ft_usleep(i->args->time_to_sleep * 1000);
}

void p_think(t_main * i)
{
	pthread_mutex_lock(i->m_died);
    printf("%ld %d is thinking\n", get_time_stamp() / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
}

void p_takefork(t_main * i)
{
	pthread_mutex_lock(i->m_died);
    printf("%ld %d has taken a fork\n", get_time_stamp() / 1000, i->id + 1);
	pthread_mutex_unlock(i->m_died);
}

void* routine(void *arg)
{
	t_main *main = (t_main *)arg;
	while (1)
	{
		p_think(main);
		pthread_mutex_lock(&main->mutex[main->id]);
		p_takefork(main);
		pthread_mutex_lock(&main->mutex[(main->id + 1) % main->args->nb_of_philo]);
	    p_takefork(main);
		p_eat(main);
		pthread_mutex_unlock(&main->mutex[main->id]);
		pthread_mutex_unlock(&main->mutex[(main->id + 1) % main->args->nb_of_philo]);
		if (main->args->nb_must_eat != -1)
			main->nb_eat++;
		if (main->args->nb_must_eat == main->nb_eat)
			break;
		p_sleep(main);
	}
	return 0;
}

void init_args(struct args * args, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong number of arguments!\n", 27);
		exit(EXIT_FAILURE);
	}
	args->nb_of_philo = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	args->nb_must_eat= -1;
	if (argc == 6)
	{
		args->nb_must_eat= atoi(argv[5]);
	}
	if ((args->nb_must_eat < 0 && argc == 6) || args->nb_of_philo < 0 || args->time_to_die < 0 || args->time_to_eat < 0 || args->time_to_sleep < 0) 
	{
		write(2, "Invalid argument!\n", 18);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	int i = 0;
	struct args args;
    pthread_t *th_onephilo;
	pthread_mutex_t m_died;
	pthread_mutex_t *mutex;
	t_main *g;

	init_args(&args, argc, argv);
	th_onephilo = malloc(sizeof(pthread_t) * args.nb_of_philo);
	mutex = malloc(sizeof(pthread_mutex_t) * args.nb_of_philo);
	g = malloc(sizeof(t_main) * args.nb_of_philo);

	pthread_mutex_init(&m_died, NULL);
	while (i < args.nb_of_philo)
	{
		pthread_mutex_init(mutex + i, NULL);
		i++;
	}
	long t = get_time_stamp() / 1000;
    for(i = 0; i < args.nb_of_philo; i++)
	{
		g[i].id = i;
		g[i].args = &args;
		g[i].mutex = mutex;
		g[i].nb_eat = 0;
		g[i].m_died = &m_died;
		g[i].last_time_eat = t;
		if (pthread_create(th_onephilo + i, NULL, &routine, &g[i]) != 0)
			write(2, "Faild to creat thread\n", 22);
		usleep(100);
	}
	int finish;
	finish = 0;
	while (finish != args.nb_of_philo)
	{
		finish = 0;
		for(i = 0; i < args.nb_of_philo; i++)
		{
			long t = get_time_stamp() / 1000;
			if (g[i].nb_eat == args.nb_must_eat)
				finish++;
			else if (t - g[i].last_time_eat >= args.time_to_die)
			{
				pthread_mutex_lock(g[i].m_died);
				if (t - g[i].last_time_eat >= args.time_to_die)
				{
    				printf("%ld %d Died\n", t, g[i].id + 1);
					exit(1);
				} 
				else
				{
					pthread_mutex_unlock(g[i].m_died);
				}
			}
		}
	}
	free(th_onephilo);
	free(mutex);
	free(g);
    return 0;
}