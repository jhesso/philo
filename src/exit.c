/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:54:59 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 12:59:25 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return ;
	// if (table->fork_locks != NULL)
	// 	free(table->fork_locks);
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table);
	}
}

int	err_msg(char *msg, char *detail, int exit_nb)
{
	if (!detail)
		printf(msg, STR_PROG_NAME);
	else
		printf(msg, STR_PROG_NAME, detail);
	return (exit_nb);
}

void	clean_exit(t_table *table, int exit_nb)
{
	if (table != NULL)
		free_table(table);
	exit (exit_nb);
}
