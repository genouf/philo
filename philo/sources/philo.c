/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:16 by genouf            #+#    #+#             */
/*   Updated: 2022/08/29 17:59:47 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_death(t_group_philo *philos, t_parsed *entry)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&entry->m_eat);
	while (i < entry->philo_num)
	{
		if (philos->philo[i].finished == 1)
		{
			entry->ph_finished = 1;
			pthread_mutex_unlock(&entry->m_eat);
			return;
		}
		if (philos->philo[i].alive == 0)
		{
			entry->philos_ok = 0;
			pthread_mutex_unlock(&entry->m_eat);
			return;
		}
		i++;
	}
	pthread_mutex_unlock(&entry->m_eat);
}

int	main(int argc, char **argv)
{
	t_parsed		entry;
	t_group_philo	philos;
	long int		start;
	//int	i;

	start = get_time();
	/* PARTIE DU PARSING */
	if (argc != 5 && argc != 6)
	{
		printf("Bad number of arguments !\n");
		return (1);
	}
	if (entry_parse(argv, argc, &entry))
	{
		printf("TOTAL TIME : %ld\n", timestamp(start));
		return (1);
	}
	/* PARTIE DES THREADS */
	if (init_philo(&philos, &entry))
		return (1);
	while (entry.philos_ok == 1 && entry.ph_finished == 0)
		check_death(&philos, &entry);
	unlock_all(&philos, &entry);
	end_philo(&philos, &entry);
	printf("TOTAL TIME : %ld\n", timestamp(start));
	return (0);
}