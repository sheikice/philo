/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:11:43 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/21 13:48:26 by jwuille          ###   ########.fr       */
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
		return (false);
	i = -1;
	while (++i < nbr && pthread_create(&(threads[i]), NULL,
			&routine, &(philo[i])) == 0)
		continue ;
	if (i != nbr)
		print_err(ERR_MALLOC);
	while (--i > -1 && pthread_join(threads[i], NULL) == 0)
		continue ;
	free(threads);
	return (true);
}
