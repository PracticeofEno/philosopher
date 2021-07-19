#include "philo.h"

void	get_first_fork(t_indivi *indivi, t_share *share)
{
	int	fork_number;

	if (check_dies(indivi, share) == 1)
		return ;
	fork_number = indivi->philo_number;
	pthread_mutex_lock(&share->fork_mutex[fork_number]);
	if (check_enable_eat(indivi, share))
	{
		if (*(share->forks + fork_number) == 0)
		{
			set_fork(share, indivi, fork_number, 1);
			indivi->state = 2;
		}
	}
	pthread_mutex_unlock(&share->fork_mutex[fork_number]);
}

void	get_second_fork(t_indivi *indivi, t_share *share)
{
	int	fork_number;

	if (check_dies(indivi, share) == 1)
		return ;
	if (share->philo_count == 1)
		return ;
	fork_number = indivi->philo_number + 1;
	if (fork_number == share->philo_count)
		fork_number = 0;
	pthread_mutex_lock(&share->fork_mutex[fork_number]);
	if (check_enable_eat(indivi, share))
	{
		if (*(share->forks + fork_number) == 0)
		{
			set_fork(share, indivi, fork_number, 1);
			indivi->state = 3;
		}
	}
	pthread_mutex_unlock(&share->fork_mutex[fork_number]);
}

void	do_eat(t_indivi *indivi, t_share *share)
{
	int	fork;
	int	fn;

	if (check_dies(indivi, share) == 1)
		return ;
	fn = indivi->philo_number;
	pthread_mutex_lock(&share->fork_mutex[fn]);
	share->eat_count[fn] = share->eat_count[fn] + 1;
	pthread_mutex_unlock(&share->fork_mutex[fn]);
	indivi->eat_count = indivi->eat_count + 1;
	print_eat_time(indivi->philo_number, indivi->eat_count, share);
	indivi->last_eat_time = get_time();
	update_min_count(share);
	indivi->sleep_number = 1;
}

void	do_sleep(t_indivi *indivi, t_share *share)
{
	int	fork;

	if (check_dies(indivi, share) == 1)
		return ;
	print_sleep(indivi->philo_number, share);
	indivi->sleep_number = 2;
}

void	do_thinking(t_indivi *indivi, t_share *share)
{
	int	fork;

	if (check_dies(indivi, share) == 1)
		return ;
	print_think(indivi->philo_number, share);
	indivi->state = 1;
}
