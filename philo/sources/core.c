/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:21:52 by genouf            #+#    #+#             */
/*   Updated: 2022/09/13 17:38:16 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_ucheck(long int time_in_ms, t_philo *philo)
{
	printf("time : %ld\n", time_in_ms);
	while (time_in_ms)
	{
		if (check_alive(philo))
			return (1);
		ft_usleep(1);
		time_in_ms--;
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_fork(philo->left_fork);
	else
		lock_fork(philo->right_fork);
	philo_print("has taken a fork", philo);
	if (check_alive(philo))
		return (1);
	if (philo->id % 2 == 0)
		lock_fork(philo->right_fork);
	else
		lock_fork(philo->left_fork);
	philo_print("has taken a fork", philo);
	if (check_alive(philo))
		return (1);
	philo_print("is eating", philo);
	pthread_mutex_lock(&philo->m_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->m_eat);
	if (ft_ucheck(philo->entry->time_to_eat, philo))
		return (1);
	unlock_fork(philo->right_fork);
	unlock_fork(philo->left_fork);
	return (0);
}

int	routine(t_philo *philo)
{
	philo_print("is thinking", philo);
	if (philo_eat(philo))
		return (1);
	philo_print("is sleeping", philo);
	if (ft_ucheck(philo->entry->time_to_sleep, philo))
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
				return (NULL);
		}
	}
	else
	{
		while (philo->eat_count > 0)
		{
			if (routine(philo))
				return (NULL);
			philo->eat_count--;
		}
	}
	pthread_mutex_lock(&philo->entry->master_eat);
	philo->finished = 1;
	pthread_mutex_unlock(&philo->entry->master_eat);
	return (NULL);
}