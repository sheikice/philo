# philo
Dinning philosopher project


===============================================================================
SUBJECT:
* Each philo is a THREAD
* one fork between each pair of philo + each fork protected with a mutex

//1 or more philo, same nbr of fork
//action: EAT - SLEEP - THINK
//EAT recquire 2 forks
// after EAT, release fork then SLEEP
// after SLEEP, THINK 
//END of SIMULATION when a philo DIES
// should nerver starve
//philo do not communicate
//philo doesnt know if one dies
// should avoid dying
gcc -fsanitize=thread -g threads.c && ./a.out

prototype: ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philo_must_eat]
==============================================================================
