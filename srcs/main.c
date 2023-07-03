/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datran <datran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:14:59 by datran            #+#    #+#             */
/*   Updated: 2023/05/30 12:03:41 by datran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	start_simulation(t_table *table)
{
	int		i;

	table->start_time = get_time_in_ms();
	i = -1;
	while (++i < table->nbs_philo)
	{
		table->philos[i].last_eat = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL, philosopher, \
		&table->philos[i]) != 0)
			error_free_msg(STR_ERR_CREATE_THREAD, table);
	}
	if (table->nbs_philo > 1)
		if (pthread_create(&table->supervisor, NULL, supervisor, table) != 0)
			error_free_msg(STR_ERR_CREATE_THREAD, table);
}

static void	destroy_mutexes(t_table *table)
{
	int		i;

	if (pthread_mutex_destroy(&table->sim_stop_lock) != 0)
		error_free_msg(STR_ERR_MUTEX_DESTROY, table);
	if (pthread_mutex_destroy(&table->write_lock) != 0)
		error_free_msg(STR_ERR_MUTEX_DESTROY, table);
	i = -1;
	while (++i < table->nbs_philo)
	{
		if (pthread_mutex_destroy(&table->forks_lock[i]) != 0)
			error_free_msg(STR_ERR_MUTEX_DESTROY, table);
		if (pthread_mutex_destroy(&table->philos[i].eat_lock) != 0)
			error_free_msg(STR_ERR_MUTEX_DESTROY, table);
	}
}

static void	stop_simulation(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->nbs_philo)
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			error_free_msg(STR_ERR_THREAD_JOIN, table);
	if (table->nbs_philo > 1)
		if (pthread_join(table->supervisor, NULL) != 0)
			error_free_msg(STR_ERR_THREAD_JOIN, table);
	destroy_mutexes(table);
	free_table(table);
}

int	main(int ac, char **av)
{
	t_table		table;

	parsing_args(ac, av, &table);
	init_table(&table);
	start_simulation(&table);
	stop_simulation(&table);
	return (0);
}
