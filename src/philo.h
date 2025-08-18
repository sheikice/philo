/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:15:45 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/17 15:44:08 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/select.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define ERR_NB_ARG "Usage: ./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philo_must_eat]\n"
# define ERR_EAT_LIMIT "Error: Invalid number_of_times_each_philo_must_eat\n"
# define EAT_LIMIT 2147483647

typedef struct s_phi
{
	int				number_of_philosophers;
	unsigned long	time_to_start;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_times_each_philo_must_eat;
}	t_phi;

typedef struct s_fork
{
	int				nbr;//from 1 to n
	pthread_mutex_t	fork_lock;
}	t_fork;

typedef struct s_meal_eaten
{
	int				nbr;//from 1 to n
	pthread_mutex_t	meal_lock;
}	t_meal_eaten;

typedef struct s_philosoph
{
	int				nbr;//from 1 to n
	t_meal_eaten	meal_eaten;
	t_fork			*left;
	t_fork			*right;
}	t_philosoph;

void	quit_error(char *str);

#endif
