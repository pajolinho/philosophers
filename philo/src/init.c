static int init_table(char **av)
{
	return (0);
}

static int	init_philo(char **av)
{
	return (0);
}

int	init_all(char **av)
{
	if (init_table(av))
		return (1);
	if (init_philo(av))
		return (1);
	return (0);
}
