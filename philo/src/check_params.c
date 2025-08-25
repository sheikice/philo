/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:53:22 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/25 20:58:10 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_valid_value(int value, int i)
{
	if (value < 0)
	{
		print_msg(ERR_POSNUM_ARG, STDERR_FILENO);
		return (false);
	}
	if (i == 1 && (value < MIN_PHILO || value > MAX_PHILO))
	{
		print_msg(ERR_NBR_PHILOSOPH, STDERR_FILENO);
		return (false);
	}
	if (i == 5 && value < MIN_MEAL)
	{
		print_msg(ERR_NBR_MEAL, STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	is_number(char *arg)
{
	int	i;

	i = 0;
	if (!(arg[i] > '0' && arg[i] <= '9') && !(arg[i] == '0' && !(arg[i + 1])))
	{
		print_msg(ERR_POSNUM_ARG, STDERR_FILENO);
		return (false);
	}
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			print_msg(ERR_POSNUM_ARG, STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}

bool	check_params(char **av)
{
	int	i;
	int	value;

	i = 0;
	while (av[++i])
	{
		if (!is_number(av[i]))
			return (false);
		value = ft_atoi(av[i]);
		if (!is_valid_value(value, i))
			return (false);
	}
	return (true);
}
