/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:37:02 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 12:14:46 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		clean_exit(&table, "invalid number of arguments\n");
	validate_input(&table, av);
	printf("valid input :)\n");
	printf("input given:\nnb_philos: %d\ntime_to_die: %d\ntime_to_eat: %d\n\
	time_to_sleep: %d\namount_must_eat: %d\n", philo.nb_philos, philo.time_to_die, \
	table.time_to_eat, table.time_to_sleep, table.amount_must_eat);
	return (0);
}
