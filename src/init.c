/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:50:31 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 14:07:00 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	 assign_forks()
*	Assigns two fork ids to each philosopher. Even-numbered philosophers
*	get their fork order switched. This is because the order in which
*	philosophers take their forks matters.
*/
static void		assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->nb_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->nb_philos;
		philo->fork[1] = philo->id;
	}
}

/*	init_philos()
*	Allocates memory for each philosopher and initializes theur values.
*	Returns a pointer to the array of philosophers or NULL
*	if initialization fails
*/
static t_philo	**init_philos(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (NULL);
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
			clean_exit(table, err_msg(STR_ERR_MUTEX, NULL, EXIT_FAILURE));
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!forks)
		clean_exit(table, err_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE));
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			clean_exit(table, err_msg(STR_ERR_MUTEX, NULL, EXIT_FAILURE));
		i++;
	}
	return (forks);
}

/*	init_global_mutexes()
*	Initializes mutex locks for forks, writing and the stop simulation flag.
*	Returns true if the initalizations were successful, false if
*	initilization failed.
*/
static bool	init_global_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
		return (false);
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
		return (false);
	return (true);
}

/* 	init_table()
*	Initializes the "dining table", the data structure containing
*	all of the program's parameters.
*	Returns a pointer to the allocated table structure
*/
t_table	*init_table(int ac, char **av, int i)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		clean_exit(table, err_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE));
	table->nb_philos = ft_atoi(av[i++]);
	table->time_to_die = ft_atoi(av[i++]);
	table->time_to_eat = ft_atoi(av[i++]);
	table->time_to_sleep = ft_atoi(av[i++]);
	table->amount_must_eat = -1;
	if (ac == 6)
		table->amount_must_eat = ft_atoi(av[i]);
	table->philos = init_philos(table);
	if (!table->philos)
		clean_exit(table, err_msg(STR_ERR_MALLOC, NULL, EXIT_FAILURE));
	if (!init_global_mutexes(table))
		clean_exit(table, err_msg(STR_ERR_MUTEX, NULL, EXIT_FAILURE));
	table->sim_stop = false;
	return (table);
}
