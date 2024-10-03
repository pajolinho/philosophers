#include "../inc/philo.h"

static int	bigger_than_zero(char **av)
{
	int	i;

	i = 0;
	while (++i < 5)
	{
		if (!(philo_atoi(av[i]) > 0))
			return (1);
	}
	return (0);
}

static int	only_nbrs(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j] && j < 10)
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (1);
			if (j == 10)
				return (1);
		}
	}
	return (0);
}

int	check_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (1);
	if (only_nbrs(av))
		return (1);
	if (bigger_than_zero(av))
		return (1);
	return (0);
}
