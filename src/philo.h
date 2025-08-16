/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:13:51 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/14 21:02:04 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
#include <sys/select.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
#include <sys/time.h>

# define ERR_NB_ARG "Usage: ./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philo_must_eat]\n"

# define EAT_LIMIT 2147483647
# define ERR_EAT_LIMIT "Error: Invalid number_of_times_each_philo_must_eat\n"

typedef struct s_phi
{
	int			number_of_philosophers;
	suseconds_t	time_to_start;
	char		*time_to_die;
	char		*time_to_eat;
	char		*time_to_sleep;
	int			number_of_times_each_philo_must_eat;
}	t_phi;

void	quit_error(char *str);

#endif
