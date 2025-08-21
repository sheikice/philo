/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:53:22 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/21 18:15:24 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_positiv(char *arg)
{
	if (ft_atoi(arg) < 0)
		return (false);
	return (true);
}

static bool	is_number(char *arg)
{
	int	i;

	i = 0;
	if (!(arg[i] > '0' && arg[i] <= '9') && !(arg[i] == '0' && !(arg[i + 1])))
		return (false);
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
	}
	return (true);
}

bool	check_params(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (!is_number(av[i]) || !is_positiv(av[i]))
		{
			print_err(ERR_POSNUM_ARG);
			return (false);
		}
	}
	return (true);
}
