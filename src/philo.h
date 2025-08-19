/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:15:45 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/19 17:22:50 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/select.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

// ====== ERR MSG ==============================================================
# define ERR_NB_ARG "Usage: ./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] \
[number_of_times_each_philo_must_eat]\n"
# define ERR_EAT_LIMIT "Error: invalid number_of_times_each_philo_must_eat\n"
# define ERR_MALLOC "Error: malloc failed\n"
# define ERR_GET_TIME "Error: gettimeofday failed\n"
# define ERR_NBR_PHILOSOPH "Error: minimum number philosopher is 1\n"
# define ERR_INIT "Error: check/init param failed\n"
# define ERR_MUTEX_INIT "Error: mutex_init failed\n"
// ====== UTILS VAR ============================================================
# define TIME_START 0

typedef struct s_param
{
	int	number_of_philosophers;
	int	time_start;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philo_must_eat;
}	t_param;

typedef struct s_fork
{
	int				nbr;
	pthread_mutex_t	fork_lock;
}	t_fork;

typedef struct s_meal_eaten
{
	int				nbr;
	pthread_mutex_t	meal_lock;
}	t_meal_eaten;

typedef struct s_philosoph
{
	int				nbr;
	t_meal_eaten	meal_eaten;
	t_fork			*left;
	t_fork			*right;
}	t_philosoph;

void	quit_error(char *str);
int		start_simulation(char **av);
int		ft_atoi(const char *str);
bool	check_params(char **av);
bool	thread_run(t_philosoph *philo, t_param param);

#endif
