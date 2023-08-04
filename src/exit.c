/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:54:59 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/04 19:31:58 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return ;
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
		free(table->fork_locks);
		free(table);
}

void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

int	err_msg(char *msg, char *detail, int exit_nb)
{
	if (!detail)
		printf(msg, STR_PROG_NAME);
	else
		printf(msg, STR_PROG_NAME, detail);
	return (exit_nb);
}

/*	failure():
*	Frees any allocated memory, prints an error message and
*	returns 0 to indicate failure.
*/
int	failure(char *msg, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (err_msg(msg, details, 0));
}

/*	error_null()
*	Frees any allocated memory, prints an error message and returns a NULL pointer.
*	Used for error management during initialization.
*/
void	*error_null(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	err_msg(str, details, EXIT_FAILURE);
	return (NULL);
}
