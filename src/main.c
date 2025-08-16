#include "philo.h"

void	philo_routine1()
{
	//while (not time_to_start)
		// continue ;
	//cycle EAT - SLEEP - THINK
}

void	phi_init(t_phi *phi, char **av)
{
	struct timeval	time;

	phi->number_of_philosophers = atoi(av[1]);
	gettimeofday(&time, NULL);
	phi->time_to_start = time.tv_usec;
	phi->time_to_die = av[2];
	phi->time_to_eat = av[3];
	phi->time_to_sleep = av[4];
	if (av[5])
		phi->number_of_times_each_philo_must_eat = atoi(av[5]);
	else
		phi->number_of_times_each_philo_must_eat = -1;
	if (phi->number_of_times_each_philo_must_eat > EAT_LIMIT
		|| phi->number_of_times_each_philo_must_eat < -1)
		quit_error(ERR_EAT_LIMIT);
	printf("%lu\n", phi->time_to_start);
}

int	main(int ac, char **av)
{
	t_phi	phi;
	
	if (ac < 5 || ac > 6)
		quit_error(ERR_NB_ARG);
	phi_init(&phi, av);
	// mutex_init write
	// mutex_init fork
	// philo_creates;
	// philo attach;
	// mutex destroy
	return (EXIT_SUCCESS);
}
