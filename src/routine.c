/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:59:36 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/20 17:05:40 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_sleep(t_param param, int philo)
{
	print_time(param, SLEEP, philo);
	if (usleep(param.time_to_sleep) < 0)
		return (false);
	return (true);
}

static bool	philo_eat(t_param param, int philo)
{
	print_time(param, EAT, philo);
	if (usleep(param.time_to_eat) < 0)
		return (false);
	return (true);
}

void	*routine(void *data)
{
	int	meal_to_eat;
	int	philo;

	meal_to_eat = ((t_philosoph *)data)->param.number_of_philosophers;
	philo = ((t_philosoph *)data)->nbr;
	while (meal_to_eat != 0)
	{
		philo_eat(((t_philosoph *)data)->param, philo);
		meal_to_eat--;
		if (meal_to_eat == 0)
			return (NULL);
		philo_sleep(((t_philosoph *)data)->param, philo);
		print_time(((t_philosoph *)data)->param, THINK, philo);
	}
	return (NULL);
}
