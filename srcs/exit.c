/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datran <datran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 12:19:06 by datran            #+#    #+#             */
/*   Updated: 2023/05/17 11:14:01 by datran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_msg(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	free_table(t_table *table)
{
	free(table->philos);
	free(table->forks_lock);
}

void	error_free_msg(char *str, t_table *table)
{
	printf("%s\n", str);
	free_table(table);
	exit(EXIT_FAILURE);
}
