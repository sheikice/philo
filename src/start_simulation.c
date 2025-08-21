/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:02:52 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/21 11:33:41 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static t_philosoph	*philo_init(t_param param, t_fork *forks)
{
	t_philosoph	*philo;
	int			i;

	i = -1;
	philo = malloc(sizeof(t_philosoph) * param.number_of_philosophers);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philosoph) * param.number_of_philosophers);
	while (++i < param.number_of_philosophers)
	{
		(philo[i]).nbr = i + 1;
		(philo[i]).right = &(forks[i]);
		if (i == param.number_of_philosophers - 1)
			(philo[i]).left = &(forks[0]);
		else
			(philo[i]).left = &(forks[i + 1]);
		(philo[i]).param = param;
	}
	return (philo);
}

static t_fork	*fork_init(t_param param)
{
	t_fork	*forks;
	int		i;

	i = -1;
	forks = malloc(sizeof(t_fork) * param.number_of_philosophers);
	if (!forks)
		return (NULL);
	memset(forks, 0, sizeof(t_fork) * param.number_of_philosophers);
	while (++i < param.number_of_philosophers)
	{
		(forks[i]).nbr = i + 1;
		if (pthread_mutex_init(&(forks[i].fork_lock), NULL) != 0)
			quit_error(ERR_MUTEX_INIT);
	}
	return (forks);
}

static int	param_init(t_param *param, char **av)
{
	struct timeval	time;

	param->number_of_philosophers = ft_atoi(av[1]);
	if (param->number_of_philosophers < 1)
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
	if (gettimeofday(&time, NULL) < 0)
		quit_error(ERR_GET_TIME);
	param->time_start = time.tv_usec / 1000 + time.tv_sec * 1000 + TIME_START;
	return (1);
}

void	start_simulation(char **av)
{
	t_param		param;
	t_fork		*forks;
	t_philosoph	*philos;

	memset(&param, 0, sizeof(t_param));
	if (!check_params(av) || !param_init(&param, av))
		quit_error(ERR_INIT);
	forks = fork_init(param);
	if (!forks)
		quit_error(ERR_MALLOC);
	philos = philo_init(param, forks);
	if (!philos)
	{
		free_forks(forks, param);
		quit_error(ERR_MALLOC);
	}
	if (!thread_run(philos))
	{
		free_forks(forks, param);
		free(philos);
		quit_error(ERR_MALLOC);
	}
	free_forks(forks, param);
	free(philos);
}
