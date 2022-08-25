
#include "../includes/philo.h"

pthread_t *init_philo(t_parsed entry)
{
	pthread_t *philo_tab;
	int		i;

	printf("philo_num : %d", entry.philo_num);
	philo_tab = (pthread_t *)malloc(sizeof(pthread_t) * entry.philo_num);
	if (philo_tab == NULL)
	{
		printf("Malloc failed !\n");
		free(entry.tab_fork);
		return (NULL);
	}
	i = 0;
	while (i < entry.philo_num)
	{
		entry.number = i + 1;
		if (pthread_create(philo_tab + i, NULL, NULL, &entry) != 0)
		{
			printf("Failed to create thread !\n");
			free(philo_tab);
			free(entry.tab_fork);
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
	while (i != entry->philo_num)
	{
		if (pthread_join(philo_tab[i], NULL) != 0)
		{
			printf("Failed to join thread !\n");
			free(philo_tab);
			free(entry->tab_fork);
			return (1);
		}
		i++;
	}
	free(philo_tab);
	free(entry->tab_fork);
	return (0);
}
