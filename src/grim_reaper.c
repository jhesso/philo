/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:10:21 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/02 19:51:03 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_simulation_stopped(t_table *table)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == true)
		res = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (res);
}

/*	set_sim_stop_flag()
*	set the sim_stop boolean to true or false depending if a simulation end
*	condition has been met
*	Only the grim reaper can modify this variable
*/
static void	set_sim_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

/*	kill_philo()
*	Kill a philosopher if time_to_die has passed since the last time they ate
*	Sets the sim_stop flag to true and writes the died status message
*	Returns true if a philosopher was killed, false if not.
*/
static bool	kill_philo(t_philo *philo)
{
	if ((get_time_in_ms() - philo->last_meal) >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

/*	end_condition_reached()
*	Check if one of the end conditions is reached
*	(if a philosopher has died or if all philos ate enough)
*	Returns true if end condition is reached, false if not
*/
static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	bool			ate_enough;

	i = 0;
	ate_enough = true;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->amount_must_eat != -1)
			if (table->philos[i]->times_ate \
				< (unsigned int)table->amount_must_eat)
				ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (table->amount_must_eat != -1 && ate_enough == true)
	{
		set_sim_stop_flag(table, true);
		return (true);
	}
	return (false);
}

/*	grim_reaper()
*	The grim reaper thread's routine. Check if a philosopher must be killed
*	and if all philosophers ate enough.
*	if one of these end conditions are reached, stop the simulation.
*/
void	*grim_reaper(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->amount_must_eat == 0)
		return (NULL);
	set_sim_stop_flag(table, false);
	start_delay(table->start_time);
	while (true)
	{
		if (end_condition_reached(table))
			return (NULL);
		usleep(300);
	}
	return (NULL);
}
