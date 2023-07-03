/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datran <datran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:49:40 by datran            #+#    #+#             */
/*   Updated: 2023/05/30 12:03:16 by datran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	is_digits(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (false);
	return (true);
}

int	str_to_integer(char *str)
{
	long	ret;
	int		i;

	i = -1;
	ret = 0;
	while (str[++i])
	{
		ret = ret * 10 + (str[i] - '0');
		if (ret > INT_MAX)
			return (-1);
	}
	return (ret);
}

void	parsing_args(int ac, char **av, t_table *table)
{
	int		i;

	if (ac < 5 || ac > 6)
		error_msg(STR_ERR_NBS_ARGS);
	i = 0;
	while (++i < ac)
		if (is_digits(av[i]) == false)
			error_msg(STR_ERR_ARGS_NOT_DIGITS);
	table->nbs_philo = str_to_integer(av[1]);
	table->time_to_die = str_to_integer(av[2]);
	table->time_to_eat = str_to_integer(av[3]);
	table->time_to_sleep = str_to_integer(av[4]);
	table->times_must_eat = -1;
	if (ac == 6)
		table->times_must_eat = str_to_integer(av[5]);
	if (table->nbs_philo == -1 || table->time_to_die == -1 \
	|| table->time_to_eat == -1 || table->time_to_sleep == -1)
		error_msg(STR_ERR_ARGS_GRT_INT_MAX);
}
