
#include "../includes/philo.h"

static	int	check_integer(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '0')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
	{
		printf("Bad argument !\n");
		return (1);
	}
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
	entry->start_time = 0;
	entry->fork_tab = NULL;
}

static pthread_mutex_t	*init_fork_tab(int philo_num)
{
	pthread_mutex_t	*fork_tab;
	int				i;

	fork_tab = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_num);
	if (fork_tab == NULL)
	{
		printf("Malloc failed !\n");
		return (NULL);
	}
	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(fork_tab + i, NULL);
		i++;
	}
	return (fork_tab);
}

static void	set_struct(char **argv, int argc, t_parsed *entry)
{
	entry->philo_num = ft_atoi(argv[1]);
	entry->time_to_die = ft_atoi(argv[2]);
	entry->time_to_eat = ft_atoi(argv[3]);
	entry->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		entry->philo_eat = ft_atoi(argv[5]);
	else
		entry->philo_eat = -1;
}

int	entry_parse(char **argv, int argc, t_parsed *entry)
{
	int			i;

	i = 1;
	while (i < argc)
	{
		if (check_integer(argv[i]) == 1)
			return (1);
		i++;
	}
	init_struct(entry);
	set_struct(argv, argc, entry);
	if (entry->philo_num == 1)
	{
		only_philo(entry);
		return (1);
	}
	entry->fork_tab = init_fork_tab(entry->philo_num);
	if (entry->fork_tab == NULL)
		return (1);
	return (0);
}
