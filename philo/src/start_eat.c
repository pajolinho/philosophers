#include "../inc/philo.h"
#include <sys/time.h>
#include <pthread.h>

int	init_threading(t_philo **philos)
{
	t_table	*table;
	int		i;

	i = philos[0]->table->nbr_philo;
	while (i > 0)
	{
		pthread_create(philos[i]->thread, NULL, *eat_rules, philos[i]);
		i--;
	}
	return (0);
}

int	eat_rules(t_philo *philo)
{

}
int	start_eat(t_philo *philo)
{
	pthread_mutex_lock()
}
