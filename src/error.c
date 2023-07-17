/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:54:59 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 12:24:33 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_exit(t_table *table, char *err_msg, int exit_nb)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
	(void)table;
	exit (exit_nb);
}
