#include "../inc/philo.h"
#include <aio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int	philo_atoi(char *str)
{
	int	negativ;
	int	nbr;

	nbr = 0;
	negativ = 1;
	if (!str)
		return (-1);
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

long long time_diff(long long past, long long pres)
{

	return (pres - past);
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	let_philo_sleep(t_table *table, long long sleep_time)
{
	long long	time;
	if (table->died == 1)
	{
		time = sleep_time * 1000;
		usleep(time);
	}
}

void	write_update(t_philo *philo, char *string)
{
	t_table	*table;

	table = philo->table;
	if (table->died == 1)
	{
		printf("%s%lld %d %s\n", GRN, get_current_time() - philo->old_time, philo->id + 1, string);
	}
}
