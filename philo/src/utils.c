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

static size_t	time_diff(size_t past, size_t pres)
{
	return (pres - past);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int p_strcmp(const char *string1, const char *string2)
{
    while (*string1 && (*string1 == *string2))
    {
        string1++;
        string2++;
    }
     if (*string1 == '\0' && *string2 == '\0')
        return (1);
    else
        return (0);
}

void	let_philo_sleep(t_philo *philo, time_t sleep_time)
{

	sleep_time += get_current_time();
	while (get_current_time() < sleep_time)
		usleep(100);	
}

void	write_update(t_philo *philo, char *string)
{
	size_t	new_time;
	size_t	time;
	
	new_time = get_current_time();
	time = time_diff(philo->old_time, new_time);
	printf("%s%zu %d %s\n", GRN, get_current_time() - philo->old_time, philo->id + 1, string);

//	philo->old_time = get_current_time();
}
