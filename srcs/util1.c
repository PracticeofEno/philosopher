#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_time_s(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_dies(t_indivi *indivi, t_share *share)
{
	long	time;
	long	time2;

	pthread_mutex_lock(&share->die_mutex);
	if (share->die == 1)
	{
		indivi->state = 0;
		pthread_mutex_unlock(&share->die_mutex);
		return (1);
	}
	time2 = get_time();
	time = time2 - indivi->last_eat_time;
	if (time > share->time_to_die)
	{
		share->die = 1;
		indivi->state = 0;
		print_die(indivi->philo_number, share);
		pthread_mutex_unlock(&share->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&share->die_mutex);
	return (0);
}

int	check_enable_eat(t_indivi *indivi, t_share *share)
{
	if (share->max_eat == 0)
	{
		if (indivi->eat_count <= share->min_eat_count)
			return (1);
		else
			return (0);
	}
	else
	{
		if (indivi->eat_count < share->max_eat)
		{
			if (indivi->eat_count <= share->min_eat_count)
				return (1);
			else
				return (0);
		}
		else
		{
			indivi->state = 0;
			share->eat_full[indivi->philo_number] = 1;
			return (0);
		}
	}
}
