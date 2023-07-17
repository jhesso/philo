/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:37:02 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 16:11:58 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_simulation(t_table *table)
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
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	stop_simulation(table);
	printf("valid input :)\n");
	printf("input given:\nnb_philos: %d\ntime_to_die: %ld\ntime_to_eat: %ld\n\
	time_to_sleep: %ld\namount_must_eat: %d\n", table->nb_philos, table->time_to_die, \
	table->time_to_eat, table->time_to_sleep, table->amount_must_eat);
	return (EXIT_SUCCESS);
}
