/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:41:22 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 12:48:07 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	long int	sign;

	sign = 1;
	n = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		str++;
		if (n < 0)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
	}
	return ((int)n * (int)sign);
}

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

static bool	check_digits(char *str)
{
	if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

bool	validate_input(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!check_digits(av[i]))
			return (err_msg(STR_ERR_INPUT_DIGIT, av[i], false));
		nb = ft_atoi(av[i]);
		if (nb < 1)
			return (err_msg(STR_ERR_INPUT_DIGIT, av[i], false));
		i++;
	}
	return (true);
}
