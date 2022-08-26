
#include "../includes/philo.h"

void	*core(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	(void)philo;
	printf("Philo id : %d\n", philo->id);
	//printf("Philo number : %d\n", philo->entry->philo_num);
	return (NULL);
}