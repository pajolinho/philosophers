#include <stdio.h>
#include <stdlib.h>
#include "../inc/philo.h"

int main(int ac, char **av)
{
	t_table	*table;
	
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (check_input(ac, av))
			return (EXIT_FAILURE);
	++av;
	if (init_all(ac, av, table))
			return (1);
	if (init_threading(table->philos))
		return (1);
	return (0);
}

