/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:11:43 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/25 11:34:42 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	simulation_end(t_param *param)
{
	pthread_mutex_lock(&(param->thread_end.end_lock));
	param->thread_end.value = true;
	pthread_mutex_unlock(&(param->thread_end.end_lock));
}

static bool	is_philo_dead(t_philosoph *philo)
{
	bool	res;

	pthread_mutex_lock(&(philo->is_dead.dead_lock));
	res = philo->is_dead.value;
	pthread_mutex_unlock(&(philo->is_dead.dead_lock));
	if (res)
	{
		simulation_end(philo->param);
		usleep(500);
		print_status(DIE_MSG, philo->nbr, &(philo->param->write));
	}
	return (res);
}

static bool	meal_check(t_philosoph *philo)
{
	bool	res;

	pthread_mutex_lock(&(philo->meal.time_lock));
	res = (philo->meal.eaten
			>= philo->param->number_of_times_each_philo_must_eat);
	pthread_mutex_unlock(&(philo->meal.time_lock));
	return (res);
}

static void	check_end_conditions(t_param *param, t_philosoph *philos)
{
	int	i;

	i = -1;
	while (1)
	{
		usleep(500);
		if (is_philo_dead(&(philos[++i])))
			return ;
		if (param->number_of_times_each_philo_must_eat
			&& philos[i].full_checked == false && meal_check(&(philos[i])))
		{
			(param->philo_full)++;
			if (param->philo_full >= param->number_of_philosophers)
				break ;
			philos[i].full_checked = true;
		}
		if (i == (param->number_of_philosophers - 1))
			i = -1;
	}
	simulation_end(param);
}

void	thread_run(t_philosoph *philo)
{
	pthread_t		threads[MAX_PHILO];
	int				i;
	int				nbr;
	bool			success;

	success = true;
	nbr = (*philo).param->number_of_philosophers;
	i = -1;
	philo->param->time_start = time_get();
	while (++i < nbr && pthread_create(&(threads[i]), NULL,
			&routine, &(philo[i])) == 0)
		continue ;
	if (i == nbr)
		check_end_conditions(philo->param, philo);
	else
	{
		success = false;
		simulation_end(philo->param);
	}
	while (--i > -1 && pthread_join(threads[i], NULL) == 0)
		continue ;
	if (success == false)
		print_msg(ERR_MALLOC, STDERR_FILENO);
}
