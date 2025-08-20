/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:15:45 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/20 16:59:29 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/select.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
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

enum e_state
{
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_param
{
	int				number_of_philosophers;
	unsigned long	time_start;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_times_each_philo_must_eat;
}	t_param;

typedef struct s_fork
{
	int				nbr;
	pthread_mutex_t	fork_lock;
}	t_fork;

typedef struct s_philosoph
{
	int				nbr;
	t_fork			*left;
	t_fork			*right;
	t_param			param;
}	t_philosoph;

void	quit_error(char *str);
int		start_simulation(char **av);
int		ft_atoi(const char *str);
bool	check_params(char **av);
void	free_forks(t_fork *fork, t_param param);
bool	thread_run(t_philosoph *philo);
void	*routine(void *data);
bool	print_time(t_param param, enum e_state state, int philo);

#endif
