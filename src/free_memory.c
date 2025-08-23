/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:24:27 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/23 19:00:15 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_fork *fork, t_param param)
{
	int	i;

	i = -1;
	while (++i < param.number_of_philosophers)
		pthread_mutex_destroy(&(fork[i].fork_lock));
}

void	free_mutex(t_param param)
{
	pthread_mutex_destroy(&(param.write));
	pthread_mutex_destroy(&(param.philo_full.full_lock));
	pthread_mutex_destroy(&(param.thread_end.end_lock));
}
