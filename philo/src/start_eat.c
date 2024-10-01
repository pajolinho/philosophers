#include "../inc/philo.h"
#include <sys/time.h>
#include <pthread.h>
//temp:
#include <stdbool.h>

// TODO: Meal time locken?
void	start_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&(philo->forks[philo->right_fork_id]));
	write_update(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->forks[philo->left_fork_id]));
	write_update(philo, "has taken a fork");
	pthread_mutex_lock(&(table->meal_lock));
	write_update(philo, "is eating");
	philo->last_eaten = get_current_time();
	pthread_mutex_unlock(&(table->meal_lock));
	let_philo_sleep(table, table->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&(philo->forks[philo->right_fork_id]));
	pthread_mutex_unlock(&(philo->forks[philo->left_fork_id]));
}

void	*eat_routine(void *arg)
{
	t_philo			*philo;
	t_table			*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2)
		let_philo_sleep(table, 10);
	while(table->died == 1)
	{
		if (philo->meals_eaten == table->must_eat && table->must_eat != -1)
			break ;
		start_eat(philo);
		write_update(philo, "is sleeping");
		let_philo_sleep(table, philo->table->time_to_sleep);
		write_update(philo, "is thinking");
	}
	return (NULL);

}

//died is one if philo is still alive
static void	grim_reaper(t_philo** philos)
{
	t_table	*table;
	int		i;
	
	i = 0;
	table = philos[i]->table;
	while(true)
	{
		while(table->died == 1 && i < table->nbr_philo) 
		{
			pthread_mutex_lock(&(table->meal_lock));
			if (time_diff(philos[i]->last_eaten, get_current_time()) > table->time_to_die)
			{
				write_update(philos[i], "died");
				table->died = 0;
			}
			pthread_mutex_unlock(&(table->meal_lock));
			usleep(1000);
			i++;
		}
		if (table->died == 0)
		{
			break;
		}
		i = 0;
		while (i < table->nbr_philo)
		{
			if (philos[i]->meals_eaten >= table->must_eat && table->must_eat != 1)
				i++;
			else
				break;
		}
		if(i == table->nbr_philo)
			break ;
	}
}

static int close_all(t_philo **philos)
{
	int	i;
	t_table	*table;

	i = 0;
	table = philos[0]->table;
	while (i < table->nbr_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&(philos[i]->forks));
		i++;
	}
	pthread_mutex_destroy(&(table->meal_lock));
	
	
}

int	init_threading(t_philo **philos)
{
	t_table	*table;
	int		i;

	i = 0;
	table = philos[0]->table;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&(philos[i]->thread), NULL, eat_routine, philos[i]))
			return (1);
		philos[i]->last_eaten = get_current_time();
		i++;
	}
	//join notfalls wanders hin
	i = 0;
	grim_reaper(philos);
	close_all(philos);
	return (NULL);
}





