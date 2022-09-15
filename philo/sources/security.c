/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   security.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:20 by genouf            #+#    #+#             */
/*   Updated: 2022/09/15 15:33:32 by genouf           ###   ########.fr       */
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
