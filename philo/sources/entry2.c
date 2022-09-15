/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:13:28 by genouf            #+#    #+#             */
/*   Updated: 2022/09/15 09:42:14 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checker_integer(char *str)
{
	int		number;
	char	*tmp;

	number = ft_atoi(str);
	tmp = ft_itoa(number);
	if (ft_strcmp(str, tmp) != 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
