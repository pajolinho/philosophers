#include "../inc/philo.h"
#include <sys/time.h>
#include <pthread.h>
//temp:
#include <stdbool.h>

// TODO: Meal time locken?
void	start_eat(t_philo *philo)
{

	pthread_mutex_lock(&philo->forks[philo->left_fork_id]);
	write_update(philo, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->right_fork_id]);
	write_update(philo, "has taken a fork");
	write_update(philo, "is eating");
	let_philo_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork_id]);
	write_update(philo, "is sleeping");
	let_philo_sleep(philo->table->time_to_sleep);
}

void	*eat_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
//	if (philo->id % 2)
//		let_philo_sleep(10);
	while(true)
	{
		start_eat(philo);
		//start_think(philo); als ersatz wird hier usleep benutzt
		usleep(10000);
	}
	return (NULL);

}

void	think_routine(t_philo *philo)
{
	
}

int	init_threading(t_philo **philos)
{
	t_table	*table;
	int		i;

	i = 0;
	table = philos[0]->table;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&philos[i]->thread, NULL, &eat_routine, philos[i]) != 0)
			return (1);
		i++;
	}
	//join notfalls wanders hin
	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	return (NULL);
}



