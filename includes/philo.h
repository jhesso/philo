/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:10:37 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/17 12:32:00 by jhesso           ###   ########.fr       */
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

# define STR_USAGE "%s usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT "%s invalid input: %s: not a valid unsigned \
integer\n"
# define STR_ERR_MALLOC "%s error: Could not allocate memory\n"

/******************************************************************************/
/*								   Structs 									  */
/******************************************************************************/

typedef struct s_table
{
	unsigned int	nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				amount_must_eat;
	t_philo			**philos; // ! I'm not sure why this is needed here and in the philo struct
}		t_table;

typedef struct	s_philo
{
	unsigned int	id;
	unsigned int	times_ate;
	unsigned int	fork[2];
	time_t			last_meal;
	t_table			*table; // ! I dont know why this is needed here...
}					t_philo;

/******************************************************************************/
/*								   Functions								  */
/******************************************************************************/

/*-----------------------------input validation-------------------------------*/
/* validation.c */
void	validate_input(t_table *table, char **av);

/*--------------------------Utils and error handling--------------------------*/
/* utils.c */
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

/* error.c */
void	clean_exit(t_table *table, char *err_msg, int exit_nb);

#endif
