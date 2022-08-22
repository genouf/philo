
#include "../includes/philo.h"

/*void	*core_thread(void *arg)
{
	while (1)
	{}
}*/

int	main(int argc, char **argv)
{
	//(void)argc;
	//(void)argv;
	t_parsed	entry;
	//pthread_t	t1;

	if (argc != 5 && argc != 6)
	{
		printf("Bad number of arguments !\n");
		return (1);
	}
	if (entry_parse(argv, argc, &entry) == -1)
		return (-1);
	printf("philo_num = %d\n", entry.philo_num);
	printf("i = %d\n", entry.tab_fork[2]);
	return (0);
}
