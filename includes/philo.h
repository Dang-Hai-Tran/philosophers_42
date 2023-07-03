/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datran <datran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:40:38 by datran            #+#    #+#             */
/*   Updated: 2023/05/30 16:17:19 by datran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

# define STR_ERR_NBS_ARGS			"Error: Numbers of arguments \
isn't correct"
# define STR_ERR_ARGS_NOT_DIGITS	"Error: Found an argument \
doesn't contain only digits"
# define STR_ERR_ARGS_GRT_INT_MAX	"Error: Found an argument \
greater than INT_MAX"
# define STR_ERR_MUTEX_INIT			"Error: Couldn't create a \
mutex with pthread_mutex_init"
# define STR_ERR_MUTEX_DESTROY		"Error: Couldn't destroy a \
mutex with pthread_mutex_destroy"
# define STR_ERR_MALLOC				"Error: Couldn't allocate \
memory with malloc"
# define STR_ERR_CREATE_THREAD		"Error: Couldn't create a \
thread with pthread_create"
# define STR_ERR_THREAD_JOIN		"Error: Couldn't join a thread \
with pthread_join"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	int					forks[2];
	int					nbs_eat;
	time_t				last_eat;
	t_table				*table;
	pthread_t			thread;
	pthread_mutex_t		eat_lock;
}	t_philo;

typedef struct s_table
{
	int					nbs_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_must_eat;
	bool				sim_stop;
	time_t				start_time;
	pthread_t			supervisor;
	t_philo				*philos;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		sim_stop_lock;
	pthread_mutex_t		*forks_lock;
}	t_table;

typedef enum s_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	TAKING_RIGHT_FORK = 4,
	TAKING_LEFT_FORK = 5
}	t_status;

// exit.c
void	error_msg(char *str);
void	free_table(t_table *table);
void	error_free_msg(char *str, t_table *table);

// parsing.c
int		str_to_integer(char *str);
void	parsing_args(int ac, char **av, t_table *table);

// time.c
time_t	get_time_in_ms(void);
void	philo_sleep(time_t time_in_ms);

// init.c
void	init_table(t_table *table);

// philosopher.c
void	write_status(t_philo *philo, t_status status);
void	*philosopher(void *data);

// supervisor.c
bool	check_sim_stop(t_table *table);
void	*supervisor(void *data);

#endif
