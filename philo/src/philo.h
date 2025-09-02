/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:15:45 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/30 16:32:32 by jwuille          ###   ########.fr       */
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
# define ERR_NBR_MEAL "Error: valid number of meal is > 0\n"
# define ERR_INIT "Error: check/init param failed\n"
# define ERR_MUTEX_INIT "Error: mutex_init failed\n"
# define ERR_POSNUM_ARG "Error: positiv numeric args recquired\n"
// ====== UTILS VAR ============================================================
# define TIME_CHECK 510
# define TIME_DEATH 1800
# define TIME_ODD 5500
# define TIME_NO_FIRST 500
# define MAIN_WAIT 55000
// ====== LIMIT VAL ============================================================
# define MIN_PHILO 1
# define MIN_MEAL 1
# define MAX_PHILO 200
// ====== PRINT STATUS =========================================================
# define SLEEP_MSG "%lu ms %d is sleeping\n"
# define DIE_MSG "%lu ms %d died\n"
# define THINK_MSG "%lu ms %d is thinking\n"
# define FORK_MSG "%lu ms %d has taken a fork\n"
# define EAT_MSG "%lu ms %d has taken a fork\n%lu ms %d is eating\n"

enum e_state
{
	EAT,
	FORK,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_meal
{
	unsigned long	time;
	pthread_mutex_t	time_lock;
	int				eaten;
}	t_meal;

typedef struct s_dead
{
	bool				value;
	pthread_mutex_t		dead_lock;
}	t_dead;

typedef struct s_start
{
	bool				value;
	pthread_mutex_t		start_lock;
}	t_start;

typedef struct s_end
{
	bool				value;
	pthread_mutex_t		end_lock;
}	t_end;

typedef struct s_param
{
	int				number_of_philosophers;
	unsigned long	time_start;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_times_each_philo_must_eat;
	t_end			thread_end;
	t_start			thread_start;
	int				philo_full;
	pthread_mutex_t	write;
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
	t_meal			meal;
	bool			full_checked;
	t_dead			is_dead;
	t_param			*param;
}	t_philosoph;

bool			check_params(char **av);
bool			end_check(t_param *param);
void			free_forks(t_fork *fork, t_param param);
void			free_mutex(t_param *param);
void			free_philos(t_philosoph *philo, t_param param);
int				ft_atoi(const char *str);
bool			philo_actions(t_param *param, t_philosoph *philo);
int				print_msg(char *str, int fd);
bool			print_status(char *str, int nbr,
					pthread_mutex_t *lock, t_param *param);
void			print_end(char *str, int nbr, pthread_mutex_t *lock);
unsigned long	time_get(void);
void			quit_error(char *str);
void			*routine(void *data);
bool			start_simulation(char **av);
void			thread_run(t_philosoph *philo);

#endif
