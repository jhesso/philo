/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:37:02 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 16:34:33 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	start_threads()
*	Launch the simulation by creating a grim reaper thread and one thread
*	per philosopher.
*	Returns true if the simulation was successfully started, false
*	if there was an error.
*/
static bool	start_threads(t_table *table)
{
	unsigned int	i;

	table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, \
			&philosopher, table->philos[i]) != 0)
			return (failure(STR_ERR_THREAD, NULL, table));
		i++;
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->grim_reaper, NULL, &grim_reaper, table) != 0)
			return (failure(STR_ERR_THREAD, NULL, table));
	}
	return (true);
}

/*	stop_treads()
*	Waits for all threads to be joined and then destroyes all mutexes
*	and frees allocated memory
*/
static void	stop_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->nb_philos > 1)
		pthread_join(table->grim_reaper, NULL);
	destroy_mutexes(table);
	free_table(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac < 5 || ac > 6)
		return (err_msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!validate_input(ac, av))
		return (EXIT_FAILURE);
	table = init_table(ac, av, 1);
	if (!table)
		return(EXIT_FAILURE);
	if (!start_threads(table))
		return (EXIT_FAILURE);
	stop_threads(table);
	printf("valid input :)\n");
	printf("input given:\nnb_philos: %d\ntime_to_die: %ld\ntime_to_eat: %ld\n\
	time_to_sleep: %ld\namount_must_eat: %d\n", table->nb_philos, table->time_to_die, \
	table->time_to_eat, table->time_to_sleep, table->amount_must_eat);
	return (EXIT_SUCCESS);
}
