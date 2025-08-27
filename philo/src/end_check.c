/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:52:02 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/27 13:56:18 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	end_check(t_param *param)
{
	bool	res;

	pthread_mutex_lock(&(param->thread_end.end_lock));
	res = param->thread_end.value;
	pthread_mutex_unlock(&(param->thread_end.end_lock));
	return (res);
}
