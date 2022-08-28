
#include "../includes/philo.h"

int	check_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->entry->philo_num)
	{
		
		if (philo->eat_count != 0)
			return (1);
		
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_parsed		entry;
	t_group_philo	philos;
	//int	i;

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
	{
		gettimeofday(&big_end, NULL);
		printf("TOTAL TIME : %f\n", time_diff(&big_start, &big_end));
		return (1);
	}

	/* PARTIE DES THREADS */
	if (init_philo(&philos, &entry) == 1)
		return (1);
	//i = 0;
	//while (check_eat(philos.philo))
	//{
	//	i++;
	//}
	end_philo(&philos, &entry);
	
	/* -------------------------------- */
	gettimeofday(&big_end, NULL);
	printf("TOTAL TIME : %f\n", time_diff(&big_start, &big_end));
	/* -------------------------------- */

	return (0);
}