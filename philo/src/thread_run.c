/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:11:43 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/20 16:22:19 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	thread_run(t_philosoph *philo)
{
	pthread_t	*threads;
	int			i;
	int			nbr;

	nbr = (*philo).param.number_of_philosophers;
	threads = malloc(sizeof(pthread_t) * nbr);
	if (!threads)
		quit_error(ERR_MALLOC);
	i = -1;
	while (++i < nbr)
	{
		if (pthread_create(&(threads[i]), NULL,
				&routine, &(philo[i])) < 0)
			quit_error("Error: thread_create failed\n");
	}
	i = -1;
	while (++i < nbr)
	{
		if (pthread_join(threads[i], NULL) < 0)
			quit_error("Error: thread_join failed\n");
	}
	free(threads);
	return (true);
}
