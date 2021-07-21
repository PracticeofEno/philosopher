#include "philo.h"

int	divide_sleep(int goal_time, t_share *share, t_indivi *indivi)
{
	long	time;

	time = get_time() + goal_time;
	usleep(goal_time * 900);
	while (time > get_time())
		usleep(share->philo_count * 2.3);
	if (indivi->state == 3)
	{
		drop_fork(indivi, share);
		indivi->state = 4;
		indivi->sleep_number = 0;
	}
	else if (indivi->state == 4)
	{
		indivi->state = 5;
		indivi->sleep_number = 0;
	}
	return (0);
}

void	drop_fork(t_indivi *indivi, t_share *share)
{
	int	left;
	int	right;

	left = indivi->philo_number;
	if (indivi->philo_number + 1 == share->philo_count)
		right = 0;
	else
		right = indivi->philo_number + 1;
	pthread_mutex_lock(&share->fork_mutex[left]);
	pthread_mutex_lock(&share->fork_mutex[right]);
	if (indivi->philo_number + 1 == share->philo_count)
	{
		*((share->forks) + 0) = 0;
		*((share->forks) + indivi->philo_number) = 0;
	}
	else
	{
		*((share->forks) + indivi->philo_number) = 0;
		*((share->forks) + indivi->philo_number + 1) = 0;
	}
	pthread_mutex_unlock(&share->fork_mutex[left]);
	pthread_mutex_unlock(&share->fork_mutex[right]);
}

void	update_min_count(t_share *share)
{
	int	i;
	int	min;

	i = 0;
	pthread_mutex_lock(&share->mc_mutex);
	min = share->eat_count[i];
	while (i < share->philo_count)
	{
		if (min > share->eat_count[i])
			min = share->eat_count[i];
		i++;
	}
	share->min_eat_count = min;
	pthread_mutex_unlock(&share->mc_mutex);
}

int	execlu_exec(t_indivi *indivi, t_share *share)
{
	void	(*func_ptr)(t_indivi *, t_share *);

	if (indivi->state == 1)
		func_ptr = get_first_fork;
	else if (indivi->state == 2)
		func_ptr = get_second_fork;
	else if (indivi->state == 3)
		func_ptr = do_eat;
	else if (indivi->state == 4)
		func_ptr = do_sleep;
	else if (indivi->state == 5)
		func_ptr = do_thinking;
	func_ptr(indivi, share);
	if (indivi->state == 0 || indivi->state == 9)
	{
		return (1);
	}
	if (indivi->sleep_number == 1)
		divide_sleep(share->time_to_eat, share, indivi);
	else if (indivi->sleep_number == 2)
		divide_sleep(share->time_to_sleep, share, indivi);
	return (0);
}

int	check_eat_full(t_share *share)
{
	int	i;

	i = 0;
	while (i < share->philo_count)
	{
		if (share->eat_full[i] != 1)
			return (0);
		i++;
	}
	return (1);
}
