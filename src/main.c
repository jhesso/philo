/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:37:02 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 14:06:08 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	printf("valid input :)\n");
	printf("input given:\nnb_philos: %d\ntime_to_die: %ld\ntime_to_eat: %ld\n\
	time_to_sleep: %ld\namount_must_eat: %d\n", table->nb_philos, table->time_to_die, \
	table->time_to_eat, table->time_to_sleep, table->amount_must_eat);
	return (0);
}
