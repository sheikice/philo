/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:53:22 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/21 18:44:18 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_valid_value(int value, int i)
{
	if (value < 0)
	{
		print_err(ERR_POSNUM_ARG);
		return (false);
	}
	if (i == 1 && (value < 1 || value > 200))
	{
		print_err(ERR_NBR_PHILOSOPH);
		return (false);
	}
	if (i == 5 && value < 1)
	{
		print_err(ERR_NBR_MEAL);
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
		print_err(ERR_POSNUM_ARG);
		return (false);
	}
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			print_err(ERR_POSNUM_ARG);
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
		value = ft_atoi(av[i]);
		if (!is_number(av[i]))
			return (false);
		if (!is_valid_value(value, i))
			return (false);
	}
	return (true);
}
