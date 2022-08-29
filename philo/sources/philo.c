/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:22:16 by genouf            #+#    #+#             */
/*   Updated: 2022/08/29 09:22:18 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	end_philo(&philos, &entry);
	printf("TOTAL TIME : %ld\n", timestamp(start));
	return (0);
}