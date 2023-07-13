/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhesso <jhesso@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:10:37 by jhesso            #+#    #+#             */
/*   Updated: 2023/07/13 16:40:51 by jhesso           ###   ########.fr       */
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
/*								Structs 									  */
/******************************************************************************/

typedef struct s_philo
{
	int	philo_amount;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	amount_must_eat;
	int	opt;
}		t_philo;

/******************************************************************************/
/*								Functions									  */
/******************************************************************************/

/*-----------------------------input validation-------------------------------*/
/* validation.c */
void	validate_input(t_philo *philo, char **av);

/*--------------------------Utils and error handling--------------------------*/
/* utils.c */
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

/* error.c */
void	clean_exit(t_philo *philo, char *err_msg);

#endif
