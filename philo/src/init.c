#include "../inc/philo.h"
#include <stdlib.h>


static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc((table->nbr_philo + 1) * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i <= table->nbr_philo)
	{
		//vielleicht protecten
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

/*static void	give_fork()
{
}*/

static int init_table(char **av, t_table *table)
{
	table->nbr_philo = philo_atoi(av[0]);
	table->time_to_die = philo_atoi(av[1]);
	table->time_to_eat = philo_atoi(av[2]);
	table->time_to_sleep = philo_atoi(av[3]);
	return (0);
}

//av wegstreichen wenn nicht gebraucht
static int	init_philo(char **av, t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i++ <= table->nbr_philo)
	{
		philo[i].id = i;
		philo[i].meals_eaten = 0;
		philo[i].status = THINKING;
		philo[i].table = table;
		philo[i].right_fork_id = i;
		philo[i].left_fork_id = (i + 1) % table->nbr_philo;
		//give_fork(philos[i])
	}
	return (0);
}

int	init_all(int ac, char **av, t_table *table)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (ac == 6)
		table->must_eat = philo_atoi(av[4]);
	if (!init_forks(table))
		return (1);
	if (init_table(av, table))
		return (1);
	if (init_philo(av, table, philo))
		return (1);
	return (0);
}
