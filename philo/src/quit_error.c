/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:15:42 by jwuille           #+#    #+#             */
/*   Updated: 2025/08/22 14:58:41 by jwuille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	quit_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (write(2, str, i) < 0)
		exit(EXIT_FAILURE);
	exit(EXIT_FAILURE);
}
