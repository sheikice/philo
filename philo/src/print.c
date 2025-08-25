/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:30:25 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/23 18:32:15 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	time_get(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print_status(char *str, int nbr, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf(str, time_get(), nbr, time_get(), nbr);
	pthread_mutex_unlock(lock);
	return (EXIT_SUCCESS);
}

int	print_msg(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (write(fd, str, i) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
