/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:21:52 by genouf            #+#    #+#             */
/*   Updated: 2022/09/14 16:06:35 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork(t_philo *philo)
{
	int	check;

	if (philo->id % 2 == 0)
		check = lock_fork(philo, philo->left_fork);
	else
		check = lock_fork(philo, philo->right_fork);
	if (check == 1)
		return (1);
	philo_print("has taken a fork", philo);
	check = 0;
	if (philo->id % 2 == 0)
		check = lock_fork(philo, philo->right_fork);
	else
		check = lock_fork(philo, philo->left_fork);
	if (check == 1)
		return (1);
	philo_print("has taken a fork", philo);
	return (0);
}

static int	philo_eat(t_philo *philo)
{
	if (take_fork(philo))
		return (1);
	if (philo_print("is eating", philo))
		return (1);
	pthread_mutex_lock(&philo->m_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->m_eat);
	if (ft_ucheck(philo->entry->time_to_eat, philo))
		return (1);
	unlock_fork(philo->right_fork);
	unlock_fork(philo->left_fork);
	return (0);
}

static int	routine(t_philo *philo, int *first)
{
	if (philo_print("is thinking", philo))
		return (1);
	if (philo->entry->philo_num % 2 != 0 && philo->entry->philo_num != 1 && *first == 1)
	{
		if (ft_ucheck(1, philo))
			return (1);
	}
	if (philo_eat(philo))
		return (1);
	if (philo_print("is sleeping", philo))
		return (1);
	if (ft_ucheck(philo->entry->time_to_sleep, philo))
		return (1);
	*first = 1;
	return (0);
}

static int	process_core(t_philo *philo, int eat_count)
{
	int	first;

	first = 0;
	if (eat_count == -1)
	{
		while (1)
		{
			if (routine(philo, &first))
				return (1);
		}
	}
	else
	{
		while (eat_count > 0)
		{
			if (routine(philo, &first))
				return (1);
			philo->eat_count--;
		}
	}
	return (0);
}

void	*core(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0 && philo->entry->philo_num != 1)
		ft_usleep(20);
	if (process_core(philo, philo->eat_count))
		return (NULL);
	pthread_mutex_lock(&philo->entry->master_eat);
	philo->finished = 1;
	pthread_mutex_unlock(&philo->entry->master_eat);
	return (NULL);
}
