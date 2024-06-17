#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>


typedef enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}	t_status;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	unsigned int	meals_eaten;
	t_status		status;
	int				right_fork_id;
	int				left_fork_id;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	struct s_philo	*philos;

}	t_table;

int	check_input(int ac, char **av);
int	philo_atoi(char *str);
int init_all(int ac, char **av, t_table *table);
size_t  start_eat(t_table *table);
#endif
