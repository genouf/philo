/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:21:52 by genouf            #+#    #+#             */
/*   Updated: 2022/09/13 11:39:48 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->entry->m_print);
	printf("%ld %d %s\n", timestamp(philo->entry->start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->entry->m_print);
}

static int	check_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->entry->m_eat);
	if (philo->entry->philos_ok == 0)
	{
		pthread_mutex_unlock(&philo->entry->m_eat);
		return (1);
	}
	if (get_time() - philo->last_eat >= philo->entry->time_to_die)
	{
		philo->alive = 0;
		pthread_mutex_unlock(&philo->entry->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->entry->m_eat);
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_fork(philo->left_fork);
	else
		lock_fork(philo->right_fork);
	if (check_alive(philo))
	{
		
		return (1);
	}
	philo_print("has taken a fork", philo);
	if (philo->id % 2 == 0)
		lock_fork(philo->right_fork);
	else
		lock_fork(philo->left_fork);
	if (check_alive(philo))
		return (1);
	philo_print("has taken a fork", philo);
	philo_print("is eating", philo);
	ft_usleep(philo->entry->time_to_eat);
	unlock_fork(philo->right_fork);
	unlock_fork(philo->left_fork);
	philo->last_eat = get_time();
	return (0);
}

static int	routine(t_philo *philo)
{
	philo_print("is thinking", philo);
	if (philo_eat(philo))
		return (1);
	if (check_alive(philo))
		return (1);
	philo_print("is sleeping", philo);
	ft_usleep(philo->entry->time_to_sleep);
	if (check_alive(philo))
		return (1);
	return (0);
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
		{
			if (routine(philo))
			{
				philo_print("died", philo);
				return (NULL);
			}
		}
	}
	else
	{
		while (philo->eat_count > 0)
		{
			if (routine(philo))
			{
				philo_print("died", philo);
				return (NULL);
			}
			philo->eat_count--;
		}
	}
	pthread_mutex_lock(&philo->entry->m_eat);
	philo->finished = 1;
	pthread_mutex_unlock(&philo->entry->m_eat);
	return (NULL);
}