#include <stdio.h>
#include <stdlib.h>
#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (check_input(ac, av))
	{
		printf("%s%s%s\n", "\033[31m", "check input",
			"\033[0m");
		return (free(table), 1);
	}
	++av;
	if (init_all(ac, av, table))
		return (free_all(table, "Error initialzing vars"), 1);
	if (init_threading(table))
		return (free_all(table, "Error while threading"), 1);
	return (0);
}

int	close_all(t_philo **philos)
{
	int		i;
	t_table	*table;

	i = 0;
	table = philos[0]->table;
	while (i < table->nbr_philo)
	{
		if (pthread_join(philos[i]->thread, NULL) != 0)
			return (free_all(table, "Error while joining threads"), 1);
		i++;
	}
	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&philos[i]->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
	free_all(table, NULL);
}

void	free_all(t_table *table, char *str)
{
	t_philo	**philos;
	int		i;

	i = -1;
	if (table->philos != NULL)
	{
		philos = table->philos;
		if (philos[0]->forks)
			free(philos[0]->forks);
		while (++i < table->nbr_philo)
			free(table->philos[i]);
		free(table->philos);
	}
	if (table)
		free(table);
	if (str)
		printf("%s%s%s\n", "\033[31m", str, "\033[0m");
}

void	*lone_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->forks[philo->right_fork_id]);
	write_update(philo, "has taken a fork");
	let_philo_sleep(philo->table, philo->table->time_to_die);
	write_update(philo, "died");
	pthread_mutex_unlock(&philo->forks[philo->right_fork_id]);
}
