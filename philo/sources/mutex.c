/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:46:13 by genouf            #+#    #+#             */
/*   Updated: 2022/08/29 17:57:16 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void lock_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	fork->taken = 0;
}

void unlock_fork(t_fork *fork)
{
	pthread_mutex_unlock(&fork->fork);
	fork->taken = 1;
}

void unlock_all(t_group_philo *philos, t_parsed *entry)
{
	int	i;

	i = 0;
	while (i < entry->philo_num)
	{
		if (philos->philo[i].left_fork->taken == 1)
			pthread_mutex_unlock(&philos->philo[i].left_fork->fork);
		if (philos->philo[i].right_fork->taken == 1)
			pthread_mutex_unlock(&philos->philo[i].right_fork->fork);
		i++;
	}
}