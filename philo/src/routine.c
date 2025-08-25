/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:59:36 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/25 20:52:27 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_param *param)
{
	pthread_mutex_lock(&(param->thread_start.start_lock));
	pthread_mutex_unlock(&(param->thread_start.start_lock));
}

void	*routine(void *data)
{
	wait_start(((t_philosoph *)data)->param);
	pthread_mutex_lock(&(((t_philosoph *)data)->meal.time_lock));
	((t_philosoph *)data)->meal.time = time_get();
	pthread_mutex_unlock(&(((t_philosoph *)data)->meal.time_lock));
	if ((((t_philosoph *)data)->nbr % 2) == 0)
		usleep(TIME_ODD);
	if (((t_philosoph *)data)->nbr > 1)
		usleep(TIME_NO_FIRST);
	while (philo_actions(((t_philosoph *)data)->param,
			(t_philosoph *)data))
		continue ;
	return (NULL);
}
