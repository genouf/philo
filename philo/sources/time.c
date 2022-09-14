/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:27 by genouf            #+#    #+#             */
/*   Updated: 2022/09/14 12:40:09 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Gettimeofday crashed !\n");
		return (-1);
	}
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

float	time_diff(struct timeval *start, struct timeval *end)
{
	return (((end->tv_sec - start->tv_sec) + 1e-6
			* (end->tv_usec - start->tv_usec)) * 1000);
}

long int	timestamp(long int start)
{
	return (get_time() - start);
}
