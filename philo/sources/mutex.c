/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:46:13 by genouf            #+#    #+#             */
/*   Updated: 2022/09/14 15:43:17 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->entry->master_eat);
	if (philo->entry->ph_finished == 1)
	{
		pthread_mutex_unlock(&philo->entry->master_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->entry->master_eat);
	return (0);
}

int	check_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	while (fork->taken == 1)
	{
		pthread_mutex_unlock(&fork->fork);
		if (check_alive(philo))
			return (1);
		ft_usleep(0.5);
	}
	pthread_mutex_unlock(&fork->fork);
	return (0);
}

int	lock_fork(t_philo *philo, t_fork *fork)
{
	if (check_fork(philo, fork))
		return (1);
	pthread_mutex_lock(&fork->fork);
	fork->taken = 1;
	pthread_mutex_unlock(&fork->fork);
	return (0);
}

void	unlock_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	fork->taken = 0;
	pthread_mutex_unlock(&fork->fork);
}

void	unlock_all(t_group_philo *philos, t_parsed *entry)
{
	int	i;

	i = 0;
	while (i < entry->philo_num)
	{
		if (philos->philo[i].left_fork->taken == 1)
		{
			pthread_mutex_unlock(&philos->philo[i].left_fork->fork);
			philos->philo[i].left_fork->taken = 0;
		}
		if (philos->philo[i].right_fork->taken == 1)
		{
			pthread_mutex_unlock(&philos->philo[i].right_fork->fork);
			philos->philo[i].right_fork->taken = 0;
		}
		i++;
	}
}
