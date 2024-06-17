#include "../inc/philo.h"

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
