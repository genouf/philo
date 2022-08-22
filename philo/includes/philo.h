
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
	int		number;
	int		*tab_fork;
}			t_parsed;

/*			TIME			*/
long int	get_time(void);
void		ft_usleep(long	int time_in_ms);

/*			PARSING			*/
int			entry_parse(char **argv, int argc, t_parsed *entry);

#endif