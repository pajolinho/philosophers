#ifndef PHILO_H
# define PHILO_H




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
	struct s_table	*table,
}	t_philo;

typedef struct s_table
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}	t_table;

int	check_input(int ac, char **av);
int	philo_atoi(char *str);


#endif
