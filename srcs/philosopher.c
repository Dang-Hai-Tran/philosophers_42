/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datran <datran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:30:08 by datran            #+#    #+#             */
/*   Updated: 2023/05/30 16:26:14 by datran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_status(t_philo *philo, t_status status)
{
	time_t		time_now;
	time_t		start_time;

	time_now = get_time_in_ms();
	start_time = philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_lock);
	if (check_sim_stop(philo->table) == true && status != DIED)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (status == DIED)
		printf("%ld %d died\n", time_now - start_time, philo->id);
	else if (status == EATING)
		printf("%ld %d is eating\n", time_now - start_time, philo->id);
	else if (status == SLEEPING)
		printf("%ld %d is sleeping\n", time_now - start_time, philo->id);
	else if (status == THINKING)
		printf("%ld %d is thinking\n", time_now - start_time, philo->id);
	else if (status == TAKING_RIGHT_FORK || status == TAKING_LEFT_FORK)
		printf("%ld %d has taken a fork\n", time_now - start_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_lock);
}

static void	eat_sleep_think_cycles(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_lock[philo->forks[0]]);
	write_status(philo, TAKING_RIGHT_FORK);
	pthread_mutex_lock(&philo->table->forks_lock[philo->forks[1]]);
	write_status(philo, TAKING_LEFT_FORK);
	write_status(philo, EATING);
	pthread_mutex_lock(&philo->eat_lock);
	philo->nbs_eat++;
	philo->last_eat = get_time_in_ms();
	pthread_mutex_unlock(&philo->eat_lock);
	philo_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks_lock[philo->forks[0]]);
	pthread_mutex_unlock(&philo->table->forks_lock[philo->forks[1]]);
	write_status(philo, SLEEPING);
	philo_sleep(philo->table->time_to_sleep);
	write_status(philo, THINKING);
}

static void	one_philo_cycles(t_philo *philo)
{
	write_status(philo, TAKING_RIGHT_FORK);
	philo_sleep(philo->table->time_to_die);
	write_status(philo, DIED);
}

static void	pair_delay(t_philo *philo)
{
	time_t	delay;

	pthread_mutex_lock(&philo->eat_lock);
	delay = (philo->table->time_to_die - (get_time_in_ms() - philo->last_eat)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->eat_lock);
	if (delay <= 0)
		delay = 1;
	if (delay > 600)
		delay = 200;
	philo_sleep(delay);
}

void	*philosopher(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->table->times_must_eat == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nbs_philo == 1)
	{
		one_philo_cycles(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		pair_delay(philo);
	while (check_sim_stop(philo->table) == false)
		eat_sleep_think_cycles(philo);
	return (NULL);
}
