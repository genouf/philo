/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:09 by genouf            #+#    #+#             */
/*   Updated: 2022/09/13 11:39:48 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	malloc_philo(t_group_philo *philos, t_parsed *entry)
{
	philos->philo_thread = (pthread_t *)malloc(sizeof(pthread_t)
			* entry->philo_num);
	if (philos->philo_thread == NULL)
	{
		printf("Malloc failed !\n");
		free_mutex_tab(entry);
		return (1);
	}
	philos->philo = (t_philo *)malloc(sizeof(t_philo) * entry->philo_num);
	if (philos->philo_thread == NULL)
	{
		printf("Malloc failed !\n");
		free_mutex_tab(entry);
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
		philo->right_fork = entry->fork_tab + (i - 1);
	philo->entry = entry;
	philo->eat_count = entry->philo_eat;
	philo->alive = 1;
	philo->last_eat = entry->start_time;
	philo->finished = 0;
}

int	init_philo(t_group_philo *philos, t_parsed *entry)
{
	int				i;

	if (malloc_philo(philos, entry) == 1)
		return (1);
	i = 0;
	entry->start_time = get_time();
	while (i < entry->philo_num)
	{
		init_struct_philo(&philos->philo[i], entry, i);
		if (pthread_create(philos->philo_thread + i, NULL, &core,
				&philos->philo[i]) != 0)
		{
			printf("Failed to create thread !\n");
			emergency_join(philos->philo_thread, i);
			free(philos->philo);
			free_mutex_tab(entry);
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
			free_mutex_tab(entry);
			free(philos->philo);
			return (1);
		}
		i++;
	}
	free_mutex_tab(entry);
	free(philos->philo_thread);
	free(philos->philo);
	return (0);
}
