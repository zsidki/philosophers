/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:23:30 by zsidki            #+#    #+#             */
/*   Updated: 2021/12/20 17:20:28 by zsidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
}					t_args;

typedef struct s_main
{
	int				id;
	long			last_time_eat;
	int				nb_eat;
	t_args			*args;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*m_died;
	pthread_t		*threads;
}					t_main;

long		get_time_stamp(void);
int			ft_atoi(const char *str);
void		ft_usleep(useconds_t usec);
void		p_eat(t_main *i);
void		p_sleep(t_main *i);
void		p_think(t_main *i);
void		p_takefork(t_main *i);
void		*routine(void *arg);
int			init_args(t_args *args, int argc, char *argv[]);
int			main(int argc, char *argv[]);
int			check_arg(char *str);
void		check_argc(int argc);
#endif
