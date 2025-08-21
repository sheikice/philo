/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:02:52 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/21 17:47:21 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_init(t_param param, t_fork *forks, t_philosoph *philo)
{
	int			i;

	i = -1;
	while (++i < param.number_of_philosophers)
	{
		(philo[i]).nbr = i + 1;
		(philo[i]).right = &(forks[i]);
		if (i == param.number_of_philosophers - 1)
			(philo[i]).left = &(forks[0]);
		else
			(philo[i]).left = &(forks[i + 1]);
		(philo[i]).param = param;
		if (pthread_mutex_init(&(philo[i].is_alive.live_lock), NULL) != 0)
			break ;
		(philo[i]).is_alive.value = false;
	}
	if (i == param.number_of_philosophers)
		return (true);
	while (i >= 0)
	{
		pthread_mutex_destroy(&(philo[i].is_alive.live_lock));
		i--;
	}
	print_err(ERR_MUTEX_INIT);
	return (false);
}

static bool	fork_init(t_param param, t_fork *forks)
{
	int		i;

	i = -1;
	while (++i < param.number_of_philosophers)
	{
		(forks[i]).nbr = i + 1;
		if (pthread_mutex_init(&(forks[i].fork_lock), NULL) != 0)
			break ;
	}
	if (i == param.number_of_philosophers)
		return (true);
	while (i >= 0)
	{
		pthread_mutex_destroy(&(forks[i].fork_lock));
		i--;
	}
	print_err(ERR_MUTEX_INIT);
	return (false);
}

static void	param_init(t_param *param, char **av)
{
	struct timeval	time;

	param->number_of_philosophers = ft_atoi(av[1]);
	if (param->number_of_philosophers < 1
		|| param->number_of_philosophers > MAX_PHILO)
		quit_error(ERR_NBR_PHILOSOPH);
	param->time_to_die = ft_atoi(av[2]) * 1000;
	param->time_to_eat = ft_atoi(av[3]) * 1000;
	param->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (!av[5])
		param->number_of_times_each_philo_must_eat = 0;
	else
	{
		param->number_of_times_each_philo_must_eat = ft_atoi(av[5]);
		if (param->number_of_times_each_philo_must_eat == 0)
			exit(EXIT_SUCCESS);
	}
	if (gettimeofday(&time, NULL) != 0)
		quit_error(ERR_GET_TIME);
	param->time_start = time.tv_usec / 1000 + time.tv_sec * 1000 + TIME_START;
	param->thread_end.value = false;
	if (pthread_mutex_init(&(param->thread_end.end_lock), NULL) != 0)
		quit_error(ERR_MUTEX_INIT);
}

void	start_simulation(char **av)
{
	t_param		param;
	t_fork		forks[MAX_PHILO];
	t_philosoph	philos[MAX_PHILO];

	memset(&param, 0, sizeof(t_param));
	check_params(av);
	param_init(&param, av);
	if (!fork_init(param, forks))
	{
		pthread_mutex_destroy(&(param.thread_end.end_lock));
		exit(EXIT_FAILURE);
	}
	if (!philo_init(param, forks, philos))
	{
		pthread_mutex_destroy(&(param.thread_end.end_lock));
		free_forks(forks, param);
		exit(EXIT_FAILURE);
	}
	thread_run(philos);
	free_forks(forks, param);
	free_philos(philos, param);
	pthread_mutex_destroy(&(param.thread_end.end_lock));
}
