/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:41:22 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/13 17:01:51 by jhesso           ###   ########.fr       */
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

void	validate_input(t_philo *philo, char **av)
{
	int	row;
	int	col;

	row = 1;
	col = 0;
	while (av[row])
	{
		if (!check_digits(av[row]))
			clean_exit(philo, "all arguments should be positive integers\n");
		row++;
	}
	philo->philo_amount = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
	{
		philo->amount_must_eat = ft_atoi(av[5]);
		philo->opt = 1;
	}
	if (philo->philo_amount < 1 || philo->time_to_die < 1 || \
		philo->time_to_eat < 1 || philo->time_to_sleep < 1 || \
		(philo->opt == 1 && philo->amount_must_eat < 1))
		clean_exit(philo, "all arguments should be positive integers\n");
}
