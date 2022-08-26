
#include "../includes/philo.h"

static int	malloc_philo(t_group_philo *philos, t_parsed *entry)
{
	philos->philo_thread = (pthread_t *)malloc(sizeof(pthread_t) * entry->philo_num);
	if (philos->philo_thread == NULL)
	{
		printf("Malloc failed !\n");
		free(entry->fork_tab);
		return (1);
	}
	philos->philo = (t_philo *)malloc(sizeof(t_philo) * entry->philo_num);
	if (philos->philo_thread == NULL)
	{
		printf("Malloc failed !\n");
		free(entry->fork_tab);
		free(philos->philo_thread);
		return (1);
	}
	return (0);
}

static void	init_struct_philo(t_philo *philo, t_parsed *entry, int i)
{
	philo->id = i + 1;
	philo->left_fork = entry->fork_tab + i;
	if (i == 0)
		philo->right_fork = entry->fork_tab + (entry->philo_num - 1);
	else
		philo->right_fork = entry->fork_tab + (i + 1);
	philo->entry = entry;
}

int	init_philo(t_group_philo *philos, t_parsed *entry)
{
	int				i;

	if (malloc_philo(philos, entry) == 1)
		return (1);
	i = 0;
	while (i < entry->philo_num)
	{
		init_struct_philo(&philos->philo[i], entry, i);
		if (pthread_create(philos->philo_thread + i, NULL, &core, &philos->philo[i]) != 0)
		{
			printf("Failed to create thread !\n");
			free(philos->philo_thread);
			free(philos->philo);
			free(entry->fork_tab);
			return (1);
		}
		i++;
	}
	return (0);
}

int	end_philo(t_group_philo *philos, t_parsed *entry)
{
	int	i;

	i = 0;
	while (i < entry->philo_num)
	{
		if (pthread_join(philos->philo_thread[i], NULL) != 0)
		{
			printf("Failed to join thread !\n");
			free(philos->philo_thread);
			free(entry->fork_tab);
			free(philos->philo);
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
	free(philos->philo_thread);
	free(entry->fork_tab);
	free(philos->philo);
	return (0);
}