/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:16 by genouf            #+#    #+#             */
/*   Updated: 2022/09/15 10:49:58 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_group_philo *philos, t_parsed *entry)
{
	int	i;

	i = 0;
	ft_usleep(2);
	while (i < entry->philo_num && entry->ph_finished == 0)
	{
		pthread_mutex_lock(&entry->mass_start);
		pthread_mutex_lock(&philos->philo[i].m_eat);
		if (get_time() - philos->philo[i].last_eat
			>= philos->philo[i].entry->time_to_die && philos->philo[i].eat_count != 0)
		{
			philos->philo[i].alive = 0;
			pthread_mutex_unlock(&philos->philo[i].m_eat);
			pthread_mutex_unlock(&entry->mass_start);
			entry->ph_finished = 1;
			philo_print("died", &philos->philo[i]);
			return ;
		}
		pthread_mutex_unlock(&entry->mass_start);
		pthread_mutex_unlock(&philos->philo[i].m_eat);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_parsed		entry;
	t_group_philo	philos;

	if (argc != 5 && argc != 6)
	{
		printf("Bad number of arguments !\n");
		return (1);
	}
	if (entry_parse(argv, argc, &entry))
		return (1);
	if (init_philo(&philos, &entry))
		return (1);
	while (entry.ph_finished == 0)
		check_death(&philos, &entry);
	end_philo(&philos, &entry);
	return (0);
}
