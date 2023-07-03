/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datran <datran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:06:58 by datran            #+#    #+#             */
/*   Updated: 2023/05/30 16:17:37 by datran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philos(t_table *table)
{
	int		i;

	table->philos = malloc(sizeof(t_philo) * table->nbs_philo);
	if (!table->philos)
		error_msg(STR_ERR_MALLOC);
	i = -1;
	while (++i < table->nbs_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].forks[0] = i;
		table->philos[i].forks[1] = (i + 1) % table->nbs_philo;
		if (i % 2 == 1)
		{
			table->philos[i].forks[1] = i;
			table->philos[i].forks[0] = (i + 1) % table->nbs_philo;
		}
		table->philos[i].nbs_eat = 0;
		table->philos[i].table = table;
	}
}

static void	init_mutexes(t_table *table)
{
	int		i;

	i = -1;
	if (pthread_mutex_init(&table->sim_stop_lock, NULL) != 0)
		error_msg(STR_ERR_MUTEX_INIT);
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		error_msg(STR_ERR_MUTEX_INIT);
	while (++i < table->nbs_philo)
	{
		if (pthread_mutex_init(&table->forks_lock[i], NULL) != 0)
			error_msg(STR_ERR_MUTEX_INIT);
		if (pthread_mutex_init(&table->philos[i].eat_lock, NULL) != 0)
			error_msg(STR_ERR_MUTEX_INIT);
	}
}

void	init_table(t_table *table)
{
	table->sim_stop = false;
	table->start_time = get_time_in_ms();
	table->forks_lock = malloc(sizeof(pthread_mutex_t) * table->nbs_philo);
	init_philos(table);
	init_mutexes(table);
}
