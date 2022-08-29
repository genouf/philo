/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:21:52 by genouf            #+#    #+#             */
/*   Updated: 2022/08/29 12:24:41 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	philo_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->entry->m_print);
	printf("%ld %d %s\n", timestamp(philo->entry->start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->entry->m_print);
}

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	philo_print("has taken a fork", philo);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	philo_print("has taken a fork", philo);
	philo_print("is eating", philo);
	ft_usleep(philo->entry->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo_print("is sleeping", philo);
	ft_usleep(philo->entry->time_to_sleep);
	philo_print("is thinking", philo);
}

void	*core(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->entry->time_to_eat / 2);
	if (philo->eat_count == -1)
	{
		while (1)
			routine(philo);
	}
	else
	{
		while (philo->eat_count > 0)
		{
			routine(philo);
			philo->eat_count--;
		}	
	}
	return (NULL);
}