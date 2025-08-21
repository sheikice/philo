/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:15:45 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/21 18:15:16 by jwuille          ###   ########.fr       */
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
# define ERR_NBR_PHILOSOPH "Error: valid number of philosophers is 1 to 200\n"
# define ERR_INIT "Error: check/init param failed\n"
# define ERR_MUTEX_INIT "Error: mutex_init failed\n"
# define ERR_POSNUM_ARG "Error: positiv numeric args recquired\n"
// ====== UTILS VAR ============================================================
# define TIME_START 0
# define MAX_PHILO 200

enum e_state
{
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_end
{
	bool			value;
	pthread_mutex_t	end_lock;
}	t_end;

typedef struct s_is_alive
{
	bool			value;
	pthread_mutex_t	live_lock;
}	t_is_alive;

typedef struct s_param
{
	int				number_of_philosophers;
	unsigned long	time_start;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_times_each_philo_must_eat;
	t_end			thread_end;
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
	t_is_alive		is_alive;
	t_param			param;
}	t_philosoph;

bool	check_params(char **av);
void	free_forks(t_fork *fork, t_param param);
void	free_philos(t_philosoph *philos, t_param param);
int		ft_atoi(const char *str);
void	print_err(char *str);
bool	print_time(t_param param, enum e_state state, int philo);
void	quit_error(char *str);
void	*routine(void *data);
bool	start_simulation(char **av);
bool	thread_run(t_philosoph *philo);

#endif
