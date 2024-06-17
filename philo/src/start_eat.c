#include "../inc/philo.h"
#include <sys/time.h>

size_t	start_eat(t_table *table)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
