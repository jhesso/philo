/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:41:22 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 12:14:46 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_digits(char *str)
{
	if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	validate_input(t_table *table, char **av)
{
	int	row;
	int	col;

	row = 1;
	col = 0;
	while (av[row])
	{
		if (!check_digits(av[row]))
			clean_exit(table, "all arguments should be positive integers\n");
		row++;
	}
	table->nb_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
	{
		table->amount_must_eat = ft_atoi(av[5]);
		table->opt = 1;
	}
	if (table->nb_philos < 1 || table->time_to_die < 1 || \
		table->time_to_eat < 1 || table->time_to_sleep < 1 || \
		(table->opt == 1 && table->amount_must_eat < 1))
		clean_exit(table, "all arguments should be positive integers\n");
}
