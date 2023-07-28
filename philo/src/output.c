/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:36:51 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/18 12:45:26 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* print_status()
*	Prints a philosophers status
*	timestamp_in_ms X status
*/
static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, str);
}

/*	write_status()
*	Prints the status of a philosopher as long as the sim is still active
*	locks the write mutex to not allow interwined messages from different
*	threads.
*/
void	write_status(t_philo *philo, bool reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (has_simulation_stopped(philo->table) == true && reaper_report == false)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_lock);
}
