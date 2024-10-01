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
	int	meals_eaten;
	//t_status		status;
	int				right_fork_id;
	int				left_fork_id;
	struct s_table	*table;
	long long			old_time;
	long long			last_eaten;
	pthread_mutex_t	*forks;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	meal_lock;
	int				died;
	int				all_ate;
	int				nbr_philo;
	long long			time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
	struct s_philo	**philos;

}	t_table;

int	check_input(int ac, char **av);
int	philo_atoi(char *str);
int init_all(int ac, char **av, t_table *table);
int	init_threading(t_philo **philos);
void    let_philo_sleep(t_table *table, long long sleep_time);
long long  get_current_time(void);
void	write_update(t_philo *philo, char *string);
long long	time_diff(long long past, long long pres);
#endif
