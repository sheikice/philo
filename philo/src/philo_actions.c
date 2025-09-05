/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:00:52 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/27 15:25:24 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	meal_update(t_philosoph *philo)
{
	unsigned long	eat_time;

	if (!print_status(EAT_MSG, philo->nbr,
			&(philo->param->write), philo->param))
		return (pthread_mutex_unlock(&(philo->right->fork_lock)),
			pthread_mutex_unlock(&(philo->left->fork_lock)), false);
	eat_time = time_get();
	pthread_mutex_lock(&(philo->meal.time_lock));
	philo->meal.time = eat_time;
	eat_time += philo->param->time_to_eat;
	(philo->meal.eaten)++;
	pthread_mutex_unlock(&(philo->meal.time_lock));
	while (time_get() < eat_time)
	{
		if (end_check(philo->param))
		{
			pthread_mutex_unlock(&(philo->right->fork_lock));
			pthread_mutex_unlock(&(philo->left->fork_lock));
			return (false);
		}
		usleep(TIME_CHECK);
	}
	return (true);
}

static bool	eat(t_philosoph *philo, t_param *param)
{
	if (philo->left->nbr > philo->right->nbr)
	{
		pthread_mutex_lock(&(philo->left->fork_lock));
		if (!print_status(FORK_MSG, philo->nbr, &(param->write), param))
			return (pthread_mutex_unlock(&(philo->left->fork_lock)), false);
		pthread_mutex_lock(&(philo->right->fork_lock));
	}
	else
	{
		pthread_mutex_lock(&(philo->right->fork_lock));
		if (!print_status(FORK_MSG, philo->nbr, &(param->write), param))
			return (pthread_mutex_unlock(&(philo->right->fork_lock)), false);
		if (philo->param->number_of_philosophers < 2)
			return (pthread_mutex_unlock(&(philo->right->fork_lock)), false);
		pthread_mutex_lock(&(philo->left->fork_lock));
	}
	if (!meal_update(philo))
		return (false);
	return (pthread_mutex_unlock(&(philo->right->fork_lock)),
		pthread_mutex_unlock(&(philo->left->fork_lock)), true);
}

bool	philo_actions(t_param *param, t_philosoph *philo)
{
	unsigned long	sleep_time;

	if (end_check(param))
		return (false);
	if (!eat(philo, param))
		return (false);
	sleep_time = time_get() + param->time_to_sleep;
	if (!print_status(SLEEP_MSG, philo->nbr, &(param->write), param))
		return (false);
	while (time_get() < sleep_time)
	{
		if (end_check(param))
			return (false);
		usleep(TIME_CHECK);
	}
	if (!print_status(THINK_MSG, philo->nbr, &(param->write), param))
		return (false);
	return (true);
}
