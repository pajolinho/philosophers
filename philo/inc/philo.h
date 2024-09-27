#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>

#define	GRN	"\x1B[32m"

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
	struct s_philo	**philos;
	unsigned int	meals_eaten;
	t_status		status;
	int				right_fork_id;
	int				left_fork_id;
	struct s_table	*table;
	size_t			old_time;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	*forks;
}	t_philo;

typedef struct s_table
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	time_t				time_to_sleep;
	int				must_eat;
	struct s_philo	**philos;

}	t_table;

int	check_input(int ac, char **av);
int	philo_atoi(char *str);
int init_all(int ac, char **av, t_table *table);
int	init_threading(t_philo **philos);
size_t  get_current_time(void);
void	write_update(t_philo *philo, char *string);
#endif
