/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:20 by genouf            #+#    #+#             */
/*   Updated: 2022/09/14 12:39:31 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex_tab(t_parsed *entry)
{
	int	i;

	i = 0;
	while (i < entry->philo_num)
	{
		pthread_mutex_destroy(&entry->fork_tab[i].fork);
		i++;
	}
	free(entry->fork_tab);
}

void	emergency_join(pthread_t *philo_thread, int i)
{
	while (i > -1)
	{
		pthread_join(philo_thread[i], NULL);
		i--;
	}
	free(philo_thread);
}
