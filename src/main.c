/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:37:02 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/13 16:59:22 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac < 5 || ac > 6)
		clean_exit(&philo, "invalid number of arguments\n");
	validate_input(&philo, av);
	printf("valid input :)\n");
	printf("input given:\nphilo_amount: %d\ntime_to_die: %d\ntime_to_eat: %d\n\
	time_to_sleep: %d\namount_must_eat: %d\n", philo.philo_amount, philo.time_to_die, \
	philo.time_to_eat, philo.time_to_sleep, philo.amount_must_eat);
	return (0);
}
