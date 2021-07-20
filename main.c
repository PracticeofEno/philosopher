#include "philo.h"

void	make_fork_mutex(t_share *share)
{				
	int				*fork_arr;
	pthread_mutex_t	*fork_mutex;
	t_indivi		**ar;
	int				i;

	i = share->philo_count;
	fork_arr = (int *)malloc(sizeof(int) * share->philo_count);
	fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* share->philo_count);
	ar = (t_indivi **)malloc(sizeof(t_indivi *) * share->philo_count);
	i = 0;
	while (i < share->philo_count)
	{
		fork_arr[i] = 0;
		pthread_mutex_init(&fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&share->print_mutex, NULL);
	pthread_mutex_init(&share->die_mutex, NULL);
	pthread_mutex_init(&share->mc_mutex, NULL);
	share->forks = fork_arr;
	share->fork_mutex = fork_mutex;
	share->p_arr = ar;
}

void	init_share_data(t_share *data, char **argv)
{
	data->philo_count = ft_atoi(*(argv + 1));
	data->time_to_die = ft_atoi(*(argv + 2));
	data->time_to_eat = ft_atoi(*(argv + 3));
	data->time_to_sleep = ft_atoi(*(argv + 4));
	data->start = 0;
	data->die = 0;
	data->min_eat_count = 0;
	data->max_eat = 0;
	make_fork_mutex(data);
}

int	main(int argc, char **argv)
{
	t_share	data;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		printf("argc is must 5, 6\n");
	else
	{
		init_share_data(&data, argv);
		if (argc == 6)
			data.max_eat = ft_atoi(*(argv + 5));
		while (i <= 200)
		{
			data.eat_count[i] = 0;
			data.eat_full[i] = 0;
			i++;
		}
		philosopher(&data);
	}
	free_share(&data);
	usleep(1000 * 1000);
	return (0);
}
