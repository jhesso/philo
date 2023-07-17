/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:10:37 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 16:58:31 by jhesso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************/
/*								Includes  									  */
/******************************************************************************/

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

/******************************************************************************/
/*                                  Macros                                    */
/******************************************************************************/

# define STR_PROG_NAME "philo:"
# define STR_USAGE "%s usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT "%s invalid input: %s: not a valid unsigned \
integer\n"
# define STR_ERR_MALLOC "%s error: Could not allocate memory\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MUTEX	"%s error: Could not create mutex.\n"

/******************************************************************************/
/*								   Structs 									  */
/******************************************************************************/

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start_time;
	pthread_t		grim_reaper;
	unsigned int	nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				amount_must_eat;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}		t_table;

typedef struct	s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	time_t				last_meal;
	pthread_mutex_t		meal_time_lock;
	t_table				*table;
}						t_philo;

/******************************************************************************/
/*								   Functions								  */
/******************************************************************************/

/*-------------------------------Input parsing--------------------------------*/
/* parsing.c */
bool	validate_input(int ac, char **av);

/*------------------------------Initialization--------------------------------*/
/* init.c */
t_table	*init_table(int ac, char **av, int i);

/*--------------------------------Simulation----------------------------------*/
/* philosopher.c */
void	*philosopher(void *data);

/* grim_reaper.c */
void	*grim_reaper(void *data);

/*--------------------------Utils and error handling--------------------------*/
/* utils.c */
int		ft_atoi(const char *str);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

/* time.c */
time_t	get_time_in_ms(void);

/* exit.c */
int		err_msg(char *msg, char *detail, int exit_nb);
void	free_table(t_table *table);
void	destroy_mutexes(t_table *table);
int		failure(char *msg, char *details, t_table *table);
void	*error_null(char *str, char *details, t_table *table);

#endif
