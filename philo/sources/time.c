
#include "../includes/philo.h"

float	time_diff(struct timeval *start, struct timeval *end)
{
	return (((end->tv_sec - start->tv_sec) + 1e-6
			* (end->tv_usec - start->tv_usec)) * 1000);
}

/*void	print_time(void)
{
	int	i;
	struct timeval start;
	struct timeval mid;
	struct timeval end;

	i = 1;
	gettimeofday(&start, NULL);
	while (i)
	{
		gettimeofday(&mid, NULL);
		if (time_diff(&start, &mid) > 0.005)
			break;
	}
	while (i)
	{
		gettimeofday(&mid, NULL);
		if (time_diff(&start, &mid) > 10000)
			break;
	}
	gettimeofday(&end, NULL);
	printf("Time spent : %f milli seconds", time_diff(&start, &end));
}*/