#include "philo.h"

void	quit_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	exit(EXIT_FAILURE);
}
