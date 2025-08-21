/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:30:25 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/21 13:44:42 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_time(t_param param, enum e_state state, int philo)
{
	struct timeval	time;
	unsigned long	time_int;

	if (gettimeofday(&time, NULL) < 0)
		return (false);
	time_int = time.tv_sec * 1000 + time.tv_usec / 1000 - param.time_start;
	if (state == EAT)
		printf("%lu ms %d has taken a fork\n", time_int, philo);
	if (state == THINK)
		printf("%lu ms %d is thinking\n", time_int, philo);
	if (state == SLEEP)
		printf("%lu ms %d is sleeping\n", time_int, philo);
	if (state == DIE)
		printf("%lu ms %d died\n", time_int, philo);
	return (true);
}

void	print_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
}
