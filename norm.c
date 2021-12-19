#include "philo.h"

int	main(int argc, char *argv[])
{
	int i = 0;
	struct args args;
	pthread_t		*th_onephilo;
	pthread_mutex_t	m_died;
	pthread_mutex_t	*fork;
	t_main			*g;

	init_args(&args, argc, argv);
	th_onephilo = malloc(sizeof(pthread_t) * args.nb_of_philo);
	fork = malloc(sizeof(pthread_mutex_t) * args.nb_of_philo);
	g = malloc(sizeof(t_main) * args.nb_of_philo);

	pthread_mutex_init(&m_died, NULL);
	
	while (i < args.nb_of_philo)
	{
		pthread_mutex_init(fork + i, NULL);
		i++;
	}
	long t = get_time_stamp() / 1000;
	i = 0;
	while(i < args.nb_of_philo)
	{
		g[i].id = i;
		g[i].args = &args;
		g[i].mutex = fork;
		g[i].nb_eat = 0;
		g[i].m_died = &m_died;
		g[i].last_time_eat = t;
		if (pthread_create(th_onephilo + i, NULL, &routine, &g[i]) != 0)
			write(2, "Faild to creat thread\n", 22);
		usleep(100);
		i++;
	}
	int finish;
	finish = 0;
	while (finish != args.nb_of_philo)
	{
		finish = 0;
		i = 0;
		while(i < args.nb_of_philo)
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
					pthread_mutex_unlock(g[i].m_died);
			}
			i++;
		}
	}
	free(th_onephilo);
	free(fork);
	free(g);
	return 0;
}
