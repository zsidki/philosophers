/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:24:06 by zsidki            #+#    #+#             */
/*   Updated: 2021/12/11 17:56:28 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// number_of_philosophers

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X is eating
// timestamp_in_ms X is sleeping
// timestamp_in_ms X is thinking
// timestamp_in_ms X died
int x = 0;
pthread_mutex_t mutex;
void time_to_eat()
{
    printf("Eating\n");
}

void time_to_sleep()
{
    printf("Sleeping\n");
}

void time_to_think()
{
    printf("Thinking\n");
}
void* routine(void *arg)
{
	for (int i= 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
	}
    // time_to_think();
    // time_to_eat();
    // time_to_sleep();
}


int main(int argc, char *argv[]) 
{
    pthread_t th_onephilo[4];
	int i;
	pthread_mutex_init(&mutex, NULL);
    for(i = 0; i < 8; i++)
	{
		if (pthread_create(th_onephilo + i, NULL, &routine, NULL) != 0)
		{
			perror("Faild to creat thread");
			return 1;
		}
		printf("THead %d has started\n", i);
	}
	for(i = 0; i < 8; i++)
	{
		if (pthread_join(th_onephilo[i], NULL) != 0)
		{  
			return 2;
		}
		printf("Thread %d has finished\n", i);

	}
	pthread_mutex_destroy(&mutex);
	printf("number of x : %d\n", x);

    return 0;
}