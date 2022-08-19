
#ifndef PHILO_H
# define PHILO_H

/*			INCLUDE			*/
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_parsed {
	int		philo_num;
	float	time_to_die;
	float	time_to_eat;
	float	time_to_sleep;
	int		philo_eat;
}			t_parsed;

/*			TIME			*/
void	print_time(void);

/*			PARSING			*/
int		entry_parse(char **argv, int argc, t_parsed *entry);

#endif