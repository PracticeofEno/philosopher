#include "philo.h"

void	detect_death(t_share *share)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	usleep(100 * share->time_to_die * 0.8);
	while (true)
	{
		i = 0;
		while (i < share->philo_count)
		{
			ret = check_dies(share->p_arr[i], share);
			i++;
		}
		if (is_end(ret, share))
			break ;
	}
}

void	wait_end(t_share *share, pthread_t *thread_arr)
{
	int	i;
	int	status;

	i = 0;
	while (i < share->philo_count)
	{
		pthread_join(thread_arr[i], (void **)&status);
		i++;
	}
	return ;
}

void	philosopher(t_share *share)
{
	int				i;
	pthread_t		thread_arr[200];
	t_indivi		*indivi;

	i = 0;
	while (i < share->philo_count)
	{
		indivi = get_init_data(share, i);
		*(share->p_arr + i) = indivi;
		pthread_create(&thread_arr[i], NULL, philo_thread, (void *)indivi);
		i++;
	}
	share->time = get_time();
	share->start = 1;
	detect_death(share);
	wait_end(share, thread_arr);
	return ;
}
