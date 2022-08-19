
#include "../includes/philo.h"

static	long	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	result;

	result = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
		neg = -neg;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * neg);
}

static	int	check_integer(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (1);
	else
		return (0);
}

static void	init_struct(t_parsed *entry)
{
	entry->philo_num = 0;
	entry->time_to_die = 0;
	entry->time_to_eat = 0;
	entry->time_to_sleep = 0;
	entry->philo_eat = 0;
}

int	entry_parse(char **argv, int argc, t_parsed *entry)
{
	int			i;

	i = 1;
	while (i < argc)
	{
		if (check_integer(argv[i]))
			return (1);
		i++;
	}
	init_struct(entry);
	entry->philo_num = ft_atoi(argv[1]);
	entry->time_to_die = ft_atoi(argv[2]);
	entry->time_to_eat = ft_atoi(argv[3]);
	entry->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		entry->philo_eat = ft_atoi(argv[5]);
	else
		entry->philo_eat = -1;
	return (0);
}
