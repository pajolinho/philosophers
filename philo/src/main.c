#include <stdio.h>
#include <stdlib.h>
#include "../inc/philo.h"

int main(int ac, char **av)
{
	if (check_input(ac, av))
			return (EXIT_FAILURE);
	++av;
	if (init_all(av))
			return (1);
	printf("%d\n", philo_atoi(av[1]));
		
}

