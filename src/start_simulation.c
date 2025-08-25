/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:02:52 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/24 22:50:17 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_init(t_param *param, t_fork *forks, t_philosoph *philo)
{
	int	i;

	i = -1;
	while (++i < param->number_of_philosophers)
	{
		memset(&(philo[i]), 0, sizeof(t_philosoph));
		(philo[i]).nbr = i + 1;
		(philo[i]).right = &(forks[i]);
		if (i == param->number_of_philosophers - 1)
			(philo[i]).left = &(forks[0]);
		else if (param->number_of_philosophers > 1)
			(philo[i]).left = &(forks[i + 1]);
		(philo[i]).param = param;
		if (pthread_mutex_init(&(philo[i].meal.time_lock), NULL) != 0)
			break ;
		if (pthread_mutex_init(&(philo[i].is_dead.dead_lock), NULL) != 0)
			break ;
	}
	if (i == param->number_of_philosophers)
		return (true);
	while (--i > -1)
		pthread_mutex_destroy(&(philo[i]).meal.time_lock);
	return (false);
}

static bool	fork_init(t_param *param, t_fork *forks)
{
	int		i;

	i = -1;
	while (++i < param->number_of_philosophers)
	{
		memset(&(forks[i]), 0, sizeof(t_fork));
		(forks[i]).nbr = i + 1;
		if (pthread_mutex_init(&(forks[i].fork_lock), NULL) != 0)
			break ;
	}
	if (i == param->number_of_philosophers)
		return (true);
	while (i >= 0)
	{
		pthread_mutex_destroy(&(forks[i].fork_lock));
		i--;
	}
	print_msg(ERR_MUTEX_INIT, STDERR_FILENO);
	return (false);
}

static bool	param_init(t_param *param, char **av)
{
	if (pthread_mutex_init(&(param->write), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(param->thread_end.end_lock), NULL) != 0)
	{
		pthread_mutex_destroy(&(param->write));
		return (false);
	}
	param->number_of_philosophers = ft_atoi(av[1]);
	param->time_to_die = ft_atoi(av[2]);
	param->time_to_eat = ft_atoi(av[3]);
	param->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		param->number_of_times_each_philo_must_eat = ft_atoi(av[5]);
	return (true);
}

bool	start_simulation(char **av)
{
	t_param		param;
	t_fork		forks[MAX_PHILO];
	t_philosoph	philos[MAX_PHILO];

	memset(&param, 0, sizeof(t_param));
	if (!check_params(av) || !param_init(&param, av))
		return (false);
	if (!fork_init(&param, forks))
	{
		free_mutex(param);
		return (false);
	}
	if (philo_init(&param, forks, philos))
	{
		thread_run(philos);
		free_philos(philos, param);
	}
	free_forks(forks, param);
	free_mutex(param);
	return (true);
}
