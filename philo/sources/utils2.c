/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:37:37 by genouf            #+#    #+#             */
/*   Updated: 2022/09/15 11:01:58 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static char	*ft_strrev(char *str)
{
	char	tmp;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(str);
	while (i < size / 2)
	{
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = tmp;
		i++;
	}
	return (str);
}

static int	size_number(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static char	*create_number(char *result, int n, long tmp)
{
	int	j;
	int	size_nb;

	size_nb = size_number(tmp);
	j = 0;
	while (size_nb > 0)
	{
		result[j] = tmp % 10 + 48;
		j++;
		tmp /= 10;
		size_nb--;
	}
	if (n < 0)
	{
		result[j] = '-';
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	tmp;
	int		i;

	tmp = n;
	i = size_number(tmp) + 1;
	if (tmp < 0)
	{
		tmp = -tmp;
		i += 1;
	}
	result = (char *)malloc(sizeof(char) * i);
	if (result == NULL)
	{
		printf("Malloc failed !\n");
		return (NULL);
	}
	if (tmp == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	return (ft_strrev(create_number(result, n, tmp)));
}
