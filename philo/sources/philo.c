
#include "../includes/philo.h"

/*static int	philo_routine(t_parsed *entry, int *f_fork, int *s_fork, long int start)
{	
	int			i;

	if (*f_fork == 1 && *s_fork == 1)
	{
		*f_fork = 0;
		*s_fork = 0;
		printf("%ld %d has taken a fork\n", get_time(), entry->number);
		printf("%ld %d is eating\n", get_time(), entry->number);
		ft_usleep(entry->philo_eat);
		*f_fork = 1;
		*s_fork = 1;
		start = get_time();
		printf("%ld %d is sleeping\n", get_time(), entry->number);
		ft_usleep(entry->time_to_sleep);
	}
	else
	{
		printf("%ld %d is thinking\n", get_time(), entry->number);
		if (entry->philo_eat != -1)
			entry->philo_eat++;
		i = entry->time_to_eat;
		while (i > 0)
		{
			ft_usleep(1);
			if (check_death(start, entry->time_to_die))
				return (1);
			i--;
		}
	}
	return (0);
}

void	*core_thread(void *arg)
{
	t_parsed	*entry;
	long int	start;

	start = get_time();
	entry = (t_parsed *)arg;
	printf("la\n");
	while (1 && entry->philo_eat != 0)
	{
		if (entry->philo_num == entry->number)
		{
			if (philo_routine(entry, entry->tab_fork + (entry->number - 1), entry->tab_fork, start))
				return (NULL);
		}
		else
		{
			if (philo_routine(entry, entry->tab_fork + (entry->number - 1), entry->tab_fork + (entry->number + 1), start))
				return (NULL);
		}
		if (entry->philo_eat != -1)
			entry->philo_eat--;
	}
	return (NULL);
}*/

int	main(int argc, char **argv)
{
	t_parsed	entry;
	pthread_t	*philo_tab;

	/* -------------------------------- */
	struct timeval big_start;
	struct timeval big_end;
	gettimeofday(&big_start, NULL);
	/* -------------------------------- */

	/* PARTIE DU PARSING */
	if (argc != 5 && argc != 6)
	{
		printf("Bad number of arguments !\n");
		return (1);
	}
	if (entry_parse(argv, argc, &entry) == 1)
		return (1);

	/* PARTIE DES THREADS */
	philo_tab = init_philo(entry);
	end_philo(philo_tab, &entry);

	/* -------------------------------- */
	gettimeofday(&big_end, NULL);
	printf("TOTAL TIME : %f\n", time_diff(&big_start, &big_end));
	/* -------------------------------- */

	return (0);
}
