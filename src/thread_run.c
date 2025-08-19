/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:11:43 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/19 17:37:29 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	int	i;

	(void) data;
	i = -1;
	while (++i < 100)
		printf("philo %d is sleeping\n", ((t_philosoph *)data)->nbr);
	return (NULL);
}

bool	thread_run(t_philosoph *philo, t_param param)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * param.number_of_philosophers);
	if (!threads)
		quit_error(ERR_MALLOC);
	i = -1;
	while (++i < param.number_of_philosophers)
	{
		printf("run thread[%d]\n", i);
		if (pthread_create(&(threads[i]), NULL,
				&routine, &(philo[i])) < 0)
			quit_error("Error: thread_create failed\n");
	}
	i = -1;
	while (++i < param.number_of_philosophers)
	{
		if (pthread_join(threads[i], NULL) < 0)
			quit_error("Error: thread_join failed\n");
	}
	return (true);
}
