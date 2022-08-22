
#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Gettimeofday crashed !\n");
		return (-1);
	}
	return (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
}

void	ft_usleep(long	int time_in_ms)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}