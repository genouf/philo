
#ifndef PHILO_H
# define PHILO_H

/*			INCLUDE			*/
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

/*			STRUCT			*/
typedef struct s_parsed {
	int					philo_num;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	int					philo_eat;
	pthread_mutex_t		*fork_tab;
}			t_parsed;

typedef struct s_philo {
	int	id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_parsed		*entry;
}			t_philo;

typedef struct s_group_philo {
	t_philo		*philo;
	pthread_t	*philo_thread;
}			t_group_philo; 

/*			PHILO			*/
void		*core_thread(void *arg);

/*			CORE			*/
void		*core(void *arg);

/*			TIME			*/
long int	get_time(void);
void		ft_usleep(long int time_in_ms)  ;
int			check_death(long int start, long int time_to_die);
float		time_diff(struct timeval *start, struct timeval *end);

/*			ENTRY			*/
int			entry_parse(char **argv, int argc, t_parsed *entry);

/*			INIT_PHILO		*/
int			init_philo(t_group_philo *philos, t_parsed *entry);
int			end_philo(t_group_philo *philos, t_parsed *entry);

/*			SECURITY		*/
void		free_mutex_tab(t_parsed *entry);
void		emergency_join(pthread_t *philo_thread, int i);

#endif