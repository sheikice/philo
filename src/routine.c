/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:59:36 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/23 18:37:26 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eat(t_philosoph *philo, int *eaten, t_param *param)
{
	if (philo->left->nbr > philo->right->nbr)
	{
		pthread_mutex_lock(&(philo->left->fork_lock));
		print_status(FORK_MSG, philo->nbr, &(param->write));
		pthread_mutex_lock(&(philo->right->fork_lock));
		print_status(EAT_MSG, philo->nbr, &(param->write));
		(*eaten)++;
		return (true);
	}
	else
	{
		pthread_mutex_lock(&(philo->right->fork_lock));
		print_status(FORK_MSG, philo->nbr, &(param->write));
		pthread_mutex_lock(&(philo->left->fork_lock));
		print_status(EAT_MSG, philo->nbr, &(param->write));
		(*eaten)++;
		return (true);
	}
	return (false);
}

static bool	philo_actions(t_param *param, t_philosoph *philo, int *eaten)
{
	if (!eat(philo, eaten, param))
		return (false);
	usleep(param->time_to_eat);
	pthread_mutex_unlock(&(philo->right->fork_lock));
	pthread_mutex_unlock(&(philo->left->fork_lock));
	print_status(SLEEP_MSG, philo->nbr, &(param->write));
	usleep(param->time_to_sleep);
	print_status(THINK_MSG, philo->nbr, &(param->write));
	return (true);
}

void	*routine(void *data)
{
	int				meals;
	int				eaten;
	int				nbr;

	eaten = 0;
	meals = ((t_philosoph *)data)->param->number_of_times_each_philo_must_eat;
	nbr = ((t_philosoph *)data)->nbr;
	while (time_get() < ((t_philosoph *)data)->param->time_start + TIME_START)
		continue ;
	usleep((nbr * 30 + (nbr % 2 == 0) * 50));
	while (!meals || (meals && (eaten != meals)))
	{
		if (!philo_actions(((t_philosoph *)data)->param,
				(t_philosoph *)data, &eaten))
			return (NULL);
	}
	return (NULL);
}
