#include "../inc/philo.h"
#include <stdlib.h>

static int init_table(char **av, t_table *table)
{
	table->nbr_philo = philo_atoi(av[0]);
	table->time_to_die = philo_atoi(av[1]);
	table->time_to_eat = philo_atoi(av[2]);
	table->time_to_sleep = philo_atoi(av[3]);
	return (0);
}

//av wegstreichen wenn nicht gebraucht
static int	init_philo(char **av, t_table *table, t_philo **philo)
{
	int	i;
	pthread_mutex_t	*forks;
	forks = (pthread_mutex_t *)malloc((table->nbr_philo + 1) * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < table->nbr_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (1);
		philo[i]->id = i;
		philo[i]->old_time = get_current_time();
		philo[i]->meals_eaten = 0;
		philo[i]->status = THINKING;
		philo[i]->table = table;
		philo[i]->philos = philo;
		philo[i]->right_fork_id = i;
		philo[i]->left_fork_id = (i + 1) % table->nbr_philo;
		pthread_mutex_init(&forks[i], NULL);
		philo[i]->forks = forks;
		i++;
	}
	return (0);
}

int	init_all(int ac, char **av, t_table *table)
{
	t_philo	**philo;

	if (ac == 6)
		table->must_eat = philo_atoi(av[4]);
	if (init_table(av, table))
		return (1);
	philo = (t_philo **)malloc(sizeof(t_philo *) * table->nbr_philo);
	if (init_philo(av, table, philo))
		return (1);
	table->philos = philo;
	return (0);
}
