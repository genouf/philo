/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:00 by genouf            #+#    #+#             */
/*   Updated: 2022/09/15 15:52:57 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	check_integer(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] == '0' && str[i + 1])
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static void	init_struct(t_parsed *entry)
{
	entry->philo_num = 0;
	entry->time_to_die = 0;
	entry->time_to_eat = 0;
	entry->time_to_sleep = 0;
	entry->philo_eat = 0;
	entry->start_time = 0;
	entry->fork_tab = NULL;
	entry->ph_finished = 0;
	pthread_mutex_init(&entry->m_print, NULL);
	pthread_mutex_init(&entry->master_eat, NULL);
	pthread_mutex_init(&entry->mass_start, NULL);
	pthread_mutex_init(&entry->finished, NULL);
}

static t_fork	*init_fork_tab(int philo_num)
{
	t_fork	*fork_tab;
	int		i;

	fork_tab = (t_fork *)malloc(sizeof(t_fork) * philo_num);
	if (fork_tab == NULL)
	{
		printf("Malloc failed !\n");
		return (NULL);
	}
	i = 0;
	while (i < philo_num)
	{
		fork_tab->taken = 0;
		pthread_mutex_init(&fork_tab[i].fork, NULL);
		i++;
	}
	return (fork_tab);
}

static int	set_struct(char **argv, int argc, t_parsed *entry)
{
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) > 250)
	{
		if (ft_atoi(argv[1]) == 0)
			printf("You can't have 0 philosopher !\n");
		else
			printf("Too many philosophers !\n");
		return (1);
	}
	entry->philo_num = ft_atoi(argv[1]);
	entry->time_to_die = ft_atoi(argv[2]);
	entry->time_to_eat = ft_atoi(argv[3]);
	entry->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		entry->philo_eat = ft_atoi(argv[5]);
	else
		entry->philo_eat = -1;
	return (0);
}

int	entry_parse(char **argv, int argc, t_parsed *entry)
{
	int			i;

	i = 1;
	while (i < argc)
	{
		if (check_integer(argv[i]) || checker_integer(argv[i]))
		{
			if (check_integer(argv[i]) == 2)
				printf("Malloc failed !\n");
			else
				printf("Bad argument !\n");
			return (1);
		}
		i++;
	}
	init_struct(entry);
	if (set_struct(argv, argc, entry))
		return (1);
	entry->fork_tab = init_fork_tab(entry->philo_num);
	if (entry->fork_tab == NULL)
		return (1);
	return (0);
}
