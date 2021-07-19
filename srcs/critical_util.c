#include "philo.h"

int		is_die(t_indivi *indivi, t_share *share)
{
	pthread_mutex_lock(&share->die_mutex);
	if (indivi->state == 0)
	{
		pthread_mutex_unlock(&share->die_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&share->die_mutex);
		return (0);
	}
}

void	set_fork(t_share *share, t_indivi *indivi, int fn, int state)
{
	long	time;

	share->forks[fn] = state;
	pthread_mutex_lock(&share->print_mutex);
	time = get_time() - share->time;
	write(1, "\e[92m ", 6);
	ft_putnbr(time);
	write(1, " \e[39mms \e[92m", 14);
	ft_putnbr(indivi->philo_number);
	write(1, "\e[39m has taken a fork '", 24);
	ft_putnbr(fn);
	write(1, "'\n", 2);
	pthread_mutex_unlock(&share->print_mutex);
}
