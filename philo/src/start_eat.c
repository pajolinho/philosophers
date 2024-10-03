
#include "../inc/philo.h"
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

static void	start_eat(t_philo *philo)
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

static void	*eat_routine(void *arg)
{
	t_philo			*philo;
	t_table			*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2)
		let_philo_sleep(table, 10);
	while (table->died == 1)
	{
		if (philo->meals_eaten == table->must_eat && table->must_eat != -1)
			break ;
		start_eat(philo);
		write_update(philo, "is sleeping");
		let_philo_sleep(table, philo->table->time_to_sleep);
		write_update(philo, "is thinking");
	}
}

static void reaper_helper(t_philo **philos, t_table *table)
{
	int	i;

	i = 0;
	while ((table->died == 1) && (i < table->nbr_philo))
	{
		if (time_diff(philos[i]->last_eaten, get_current_time())
			> table->time_to_die)
		{
			write_update(philos[i], "died");
			table->died = 0;
		}
		usleep(100);
		i++;
	}
}

static void	grim_reaper(t_philo **philos, t_table *table)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	while (j == 0)
	{
		pthread_mutex_lock(&(table->meal_lock));
		reaper_helper(philos, table);
		pthread_mutex_unlock(&(table->meal_lock));
		if (table->died == 0)
			break ;
		i = 0;
		k = 0;
		while (k < table->nbr_philo)
		{
			if (philos[k]->meals_eaten >= table->must_eat
				&& table->must_eat != -1)
				i++;
			k++;
		}
		if (i == table->nbr_philo)
			j = 1;
		usleep(100);
	}
}

int	init_threading(t_table *table)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = table->philos;
	if (table->nbr_philo == 1)
		pthread_create(&philos[0]->thread, NULL, *lone_philo, philos[0]);
	else
	{
		while (i < table->nbr_philo)
		{
			if (pthread_create(&philos[i]->thread, NULL,
					*eat_routine, philos[i]))
				return (free_all(table, "error while creating thread"), 1);
			pthread_mutex_lock(&(table->meal_lock));
			philos[i]->last_eaten = get_current_time();
			pthread_mutex_unlock(&(table->meal_lock));
			i++;
		}
		grim_reaper(philos, table);
	}
	close_all(philos);
	return (0);
}
