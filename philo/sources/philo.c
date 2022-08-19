
#include "../includes/philo.h"

/*int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (1);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}*/

void	*core_thread(void *arg)
{
	
}

int	main(int argc, char **argv)
{
	t_parsed	entry;
	pthread_t	t1;

	if (argc != 5 || argc != 6)
	{
		printf("Bad number of arguments !\n");
		return (1);
	}

	return (0);
}
