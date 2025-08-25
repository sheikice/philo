/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:24:27 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/20 15:53:38 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_fork *fork, t_param param)
{
	int	i;

	i = -1;
	while (++i < param.number_of_philosophers)
		pthread_mutex_destroy(&(fork[i].fork_lock));
	free(fork);
}
