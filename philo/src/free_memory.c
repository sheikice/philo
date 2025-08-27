/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:24:27 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/27 14:54:39 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philosoph *philo, t_param param)
{
	int	i;

	i = -1;
	while (++i < param.number_of_philosophers)
		pthread_mutex_destroy(&(philo[i].meal.time_lock));
}

void	free_forks(t_fork *fork, t_param param)
{
	int	i;

	i = -1;
	while (++i < param.number_of_philosophers)
		pthread_mutex_destroy(&(fork[i].fork_lock));
}

void	free_mutex(t_param *param)
{
	pthread_mutex_destroy(&(param->write));
	pthread_mutex_destroy(&(param->thread_end.end_lock));
	pthread_mutex_destroy(&(param->thread_start.start_lock));
}
