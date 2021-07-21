#include "philo.h"

t_indivi	*get_init_data(t_share *data, int i)
{
	t_indivi	*tmp;

	tmp = (t_indivi *)malloc(sizeof(t_indivi));
	if (!tmp)
		return (0);
	tmp->philo_number = i;
	tmp->time_to_die = data->time_to_die;
	tmp->time_to_eat = data->time_to_eat;
	tmp->time_to_sleep = data->time_to_sleep;
	tmp->share = data;
	tmp->loop = 1;
	tmp->state = 1;
	tmp->eat_count = 0;
	tmp->sleep_number = 0;
	return (tmp);
}

void	*philo_thread(void *thread_data)
{
	t_share		*share;
	t_indivi	*indivi;

	indivi = (t_indivi *)thread_data;
	share = indivi->share;
	while (true)
	{
		if (share->start)
			break ;
	}
	indivi->last_eat_time = share->time;
	if (indivi->philo_number % 2 == 1)
		divide_sleep(share->time_to_eat * 0.8, share, indivi);
	while (true)
	{
		if (execlu_exec(indivi, share) == 1)
			break ;
	}
	free(indivi);
	return (0);
}
