
#include "../includes/philo.h"

int	check_sleep(long int start, t_parsed *entry)
{
	int	i;

	i = entry->time_to_die;
	while (i > 0)
	{
		if (check_death(start, entry->time_to_die))
			return (1);
		ft_usleep(1);
		i--;
	}
	return (0);
}

void	*core(void *arg)
{
	t_philo		*philo;
	//long int	start;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->entry->time_to_sleep);
	//start = get_time();
	while (philo->eat_count > 0 && 1)
	{
		//printf("%ld %d is thinking\n", get_time(), philo->id);
		pthread_mutex_lock(philo->left_fork);
		//printf("%ld %d has taken a fork\n", get_time(), philo->id);
		pthread_mutex_lock(philo->right_fork);
		//printf("%ld %d has taken a fork\n", get_time(), philo->id);
		//printf("%ld %d is eating\n", get_time(), philo->id);
		ft_usleep(philo->entry->time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		//start = get_time();
		philo->eat_count--;
		//printf("%ld %d is sleeping\n", get_time(), philo->id);
		ft_usleep(philo->entry->time_to_sleep);
	}
	return (NULL);
}