/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:00:52 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/25 19:39:45 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_dead(t_philosoph *philo)
{
	unsigned long	death_time;
	unsigned long	actual_time;

	death_time = philo->meal.time + philo->param->time_to_die;
	actual_time = time_get();
	if (actual_time > death_time)
	{
		pthread_mutex_lock(&(philo->is_dead.dead_lock));
		philo->is_dead.value = true;
		pthread_mutex_unlock(&(philo->is_dead.dead_lock));
		return (true);
	}
	return (false);
}

static bool	end_check(t_param *param)
{
	bool	res;

	pthread_mutex_lock(&(param->thread_end.end_lock));
	res = param->thread_end.value;
	pthread_mutex_unlock(&(param->thread_end.end_lock));
	return (res);
}

static bool	meal_update(t_philosoph *philo)
{
	unsigned long	eat_time;

	print_status(EAT_MSG, philo->nbr, &(philo->param->write));
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
		usleep(330);
	}
	return (true);
}

static bool	eat(t_philosoph *philo, t_param *param)
{
	if (philo->left->nbr > philo->right->nbr)
	{
		pthread_mutex_lock(&(philo->left->fork_lock));
		print_status(FORK_MSG, philo->nbr, &(param->write));
		pthread_mutex_lock(&(philo->right->fork_lock));
	}
	else
	{
		pthread_mutex_lock(&(philo->right->fork_lock));
		print_status(FORK_MSG, philo->nbr, &(param->write));
		if (philo->param->number_of_philosophers < 2)
		{
			pthread_mutex_unlock(&(philo->right->fork_lock));
			while (!is_dead(philo))
				continue ;
			return (false);
		}
		pthread_mutex_lock(&(philo->left->fork_lock));
	}
	if (!meal_update(philo))
		return (false);
	pthread_mutex_unlock(&(philo->right->fork_lock));
	pthread_mutex_unlock(&(philo->left->fork_lock));
	return (true);
}

bool	philo_actions(t_param *param, t_philosoph *philo)
{
	unsigned long	sleep_time;

	if (end_check(param) || is_dead(philo))
		return (false);
	if (!eat(philo, param))
		return (false);
	sleep_time = time_get() + param->time_to_sleep;
	print_status(SLEEP_MSG, philo->nbr, &(param->write));
	while (time_get() < sleep_time)
	{
		if (end_check(param) || is_dead(philo))
			return (false);
		usleep(330);
	}
	print_status(THINK_MSG, philo->nbr, &(param->write));
	return (true);
}
