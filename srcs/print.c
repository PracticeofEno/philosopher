#include "philo.h"

void	print_eat_time(int number, int eat_count, t_share *share)
{
	long time;

	pthread_mutex_lock(&share->print_mutex);
	time = get_time() - share->time;
	write(1, "\e[92m ", 6);
	ft_putnbr((int)time);
	write(1, " \e[39mms \e[92m", 14);
	ft_putnbr(number);
	write(1, "\e[39m is eating : ", 18);
	ft_putnbr(eat_count);
	write(1, "\n", 1);
	pthread_mutex_unlock(&share->print_mutex);
}

void	print_sleep(int number, t_share *share)
{
	long	time;

	pthread_mutex_lock(&share->print_mutex);
	time = get_time() - share->time;
	write(1, "\e[92m ", 6);
	ft_putnbr((int)time);
	write(1, " \e[39mms \e[92m", 14);
	ft_putnbr(number);
	write(1, "\e[39m is sleeping\n", 18);
	pthread_mutex_unlock(&share->print_mutex);
}

void	print_think(int number, t_share *share)
{
	long	time;

	pthread_mutex_lock(&share->print_mutex);
	time = get_time() - share->time;
	write(1, "\e[92m ", 6);
	ft_putnbr((int)time);
	write(1, " \e[39mms \e[92m", 14);
	ft_putnbr(number);
	write(1, "\e[39m is thinking\n", 18);
	pthread_mutex_unlock(&share->print_mutex);
}

void	print_die(int number, t_share *share)
{
	long	time;

	pthread_mutex_lock(&share->print_mutex);
	time = get_time() - share->time;
	write(1, "\e[92m ", 6);
	ft_putnbr((int)time);
	write(1, " \e[39mms \e[92m", 14);
	ft_putnbr(number);
	write(1, " \e[39m \e[92m", 12);
	write(1, "\e[39m is died", 13);
	write(1, "\n", 1);
	pthread_mutex_unlock(&share->print_mutex);
}
