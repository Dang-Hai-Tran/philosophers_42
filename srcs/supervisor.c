/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datran <datran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:09:11 by datran            #+#    #+#             */
/*   Updated: 2023/05/30 16:20:21 by datran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_sim_stop(t_table *table)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

bool	check_sim_stop(t_table *table)
{
	bool	sim_stop;

	pthread_mutex_lock(&table->sim_stop_lock);
	sim_stop = table->sim_stop;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (sim_stop);
}

static bool	monitoring(t_table *table)
{
	int		i;
	time_t	time_now;
	bool	all_eat_max;

	i = -1;
	time_now = get_time_in_ms();
	all_eat_max = true;
	while (++i < table->nbs_philo)
	{
		pthread_mutex_lock(&table->philos[i].eat_lock);
		if (time_now - table->philos[i].last_eat >= table->time_to_die)
		{
			set_sim_stop(table);
			write_status(&table->philos[i], DIED);
			pthread_mutex_unlock(&table->philos[i].eat_lock);
			return (true);
		}
		if (table->times_must_eat != -1 && table->philos[i].nbs_eat < table->times_must_eat)
			all_eat_max = false;
		pthread_mutex_unlock(&table->philos[i].eat_lock);
	}
	if (table->times_must_eat != -1 && all_eat_max == true)
	{
		set_sim_stop(table);
		return (true);
	}
	return (false);
}

void	*supervisor(void *data)
{
	t_table		*table;

	table = (t_table *)data;
	if (table->times_must_eat == 0)
		return (NULL);
	while (monitoring(table) == false)
		usleep(1000);
	return (NULL);
}
