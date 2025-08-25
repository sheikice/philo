/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:59:36 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/25 12:01:00 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	pthread_mutex_lock(&(((t_philosoph *)data)->meal.time_lock));
	((t_philosoph *)data)->meal.time = time_get();
	pthread_mutex_unlock(&(((t_philosoph *)data)->meal.time_lock));
	if ((((t_philosoph *)data)->nbr % 2) == 0)
		usleep(350);
	if (((t_philosoph *)data)->nbr > 1)
		usleep(100);
	while (philo_actions(((t_philosoph *)data)->param,
			(t_philosoph *)data))
		continue ;
	return (NULL);
}
