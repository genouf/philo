/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:33 by genouf            #+#    #+#             */
/*   Updated: 2022/09/13 17:37:57 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	result;

	result = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
		neg = -neg;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * neg);
}

void	philo_print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->entry->m_print);
	printf("%ld %d %s\n", timestamp(philo->entry->start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->entry->m_print);
}

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