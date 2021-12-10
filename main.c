/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:24:06 by zsidki            #+#    #+#             */
/*   Updated: 2021/12/10 21:08:43 by zsidki           ###   ########.fr       */
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


int x = 2;
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
void* routine()
{
    time_to_think();
    time_to_eat();
    time_to_sleep();
}


int main(int argc, char* argv[]) 
{
    pthread_t t1;
    t1 = NULL;
    if (pthread_create(&t1, NULL, &routine, NULL))
    {
        return 1;
    }
    // if (pthread_join(t1, NULL))
    // {
    //     return 3;
    // }
    // if (pthread_join(t2, NULL))
    // {
    //     return 3;
    // }
    return 0;
}