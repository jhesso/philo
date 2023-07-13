/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:54:59 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/13 16:48:21 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_exit(t_philo *philo, char *err_msg)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
	(void)philo;
	exit (0);
}
