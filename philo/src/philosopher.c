/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:00:39 by jhesso            #+#    #+#             */
/*   Updated: 2023/08/02 18:19:49 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	philo_wait(philo->table, philo->table->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	return (NULL);
}

static void	eat_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	write_status(philo, false, GOT_FORK_2);
	write_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_wait(philo->table, philo->table->time_to_eat);
	if (!has_simulation_stopped(philo->table))
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate++;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	philo_wait(philo->table, philo->table->time_to_sleep);
}

static void	think_routine(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->table->time_to_die - \
	(get_time_in_ms() - philo->last_meal) - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!silent)
		write_status(philo, false, THINKING);
	philo_wait(philo->table, time_to_think);
}

/*	philosopher()
*	The philosopher thread routine. The philosopher must eat, sleep and think
*	philosophers with an even id will start by thinking to allow odd-id
*	philosophers to start eating first avoiding deadlocks
*/
void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->amount_must_eat == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	start_delay(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nb_philos == 1)
		return (one_philo_routine(philo));
	else if (philo->id % 2)
		think_routine(philo, true);
		// usleep(200);
	while (!has_simulation_stopped(philo->table))
	{
		eat_sleep_routine(philo);
		think_routine(philo, false);
		// write_status(philo, false, THINKING);
	}
	return (NULL);
}
