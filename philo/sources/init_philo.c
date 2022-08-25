
#include "../includes/philo.h"

pthread_t *init_philo(t_parsed *entry)
{
	pthread_t	*philo_tab;
	t_philo		philo;
	int		i;

	philo_tab = (pthread_t *)malloc(sizeof(pthread_t) * entry->philo_num);
	if (philo_tab == NULL)
	{
		printf("Malloc failed !\n");
		free(entry->fork_tab);
		return (NULL);
	}
	i = 0;
	while (i < entry->philo_num)
	{
		philo.id = i + 1;
		philo.left_fork = entry->fork_tab + i;
		if (i == 0)
			philo.right_fork = entry->fork_tab + (entry->philo_num - 1);
		else
			philo.right_fork = entry->fork_tab + (i + 1);
		if (pthread_create(philo_tab + i, NULL, NULL, &philo) != 0)
		{
			printf("Failed to create thread !\n");
			free(philo_tab);
			free(entry->fork_tab);
			return (NULL);
		}
		i++;
	}
	return (philo_tab);
}

int	end_philo(pthread_t *philo_tab, t_parsed *entry)
{
	int	i;

	i = 0;
	while (i < entry->philo_num)
	{
		if (pthread_join(philo_tab[i], NULL) != 0)
		{
			printf("Failed to join thread !\n");
			free(philo_tab);
			free(entry->fork_tab);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < entry->philo_num)
	{
		pthread_mutex_destroy(entry->fork_tab + i);
		i++;
	}
	free(philo_tab);
	free(entry->fork_tab);
	return (0);
}
