/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:33 by genouf            #+#    #+#             */
/*   Updated: 2022/09/15 09:35:33 by genouf           ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	philo_print(char *msg, t_philo *philo)
{
	if (check_alive(philo) && ft_strcmp("died", msg) != 0)
		return (1);
	pthread_mutex_lock(&philo->entry->m_print);
	printf("%ld %d %s\n", timestamp(philo->entry->start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->entry->m_print);
	return (0);
}

int	ft_ucheck(long int time_in_ms, t_philo *philo)
{
	long int start;
	
	start = get_time();
	while (get_time() - start < time_in_ms)
	{
		if (check_alive(philo))
			return (1);
		usleep(30);
	}
	return (0);
}
