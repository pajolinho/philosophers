#include "../inc/philo.h"
#include <aio.h>
int	philo_atoi(char *str)
{
	int	negativ;
	int	nbr;

	nbr = 0;
	negativ = 1;
	while (*str == ' ' || (*str > 8 && *str < 14))
		++str;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negativ *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 +  (*str++ - '0');
	return (nbr * negativ);
}

size_t	get_time_of_the_day(t_table *table)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
