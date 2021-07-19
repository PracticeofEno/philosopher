#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <errno.h>
# include <pthread.h>
# include "libft.h"

typedef struct s_indivi_data	t_indivi;
typedef struct s_share			t_share;

struct	s_share
{
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		die_mutex;
	pthread_mutex_t		et_mutex;
	pthread_mutex_t		mc_mutex;
	t_indivi			**p_arr;
	long				time;
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					die;
	int					eat_count[201];
	int					eat_full[200];
	int					min_eat_count;
	int					start;
	int					max_eat;
	int					*forks;
};

struct	s_indivi_data {
	t_share	*share;
	long	last_eat_time;
	int		philo_number;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		loop;
	int		state;
	int		eat_count;
	int		sleep_number;
};

t_indivi	*get_init_data(t_share *data, int i);
void		philosopher(t_share *data);
void		*philo_thread(void *thread_data);
void		get_first_fork(t_indivi *indivi, t_share *share);
void		get_second_fork(t_indivi *indivi, t_share *share);
void		do_eat(t_indivi *indivi, t_share *share);
void		do_sleep(t_indivi *indivi, t_share *share);
void		do_thinking(t_indivi *indivi, t_share *share);
int			execlu_exec(t_indivi *indivi, t_share *share);
long		get_time(void);
long		get_time_s(struct timeval time);
int			check_dies(t_indivi *indivi, t_share *share);
int			try_catch_fork(t_indivi *indivi, t_share *share, int fork_number);
void		drop_fork(t_indivi *indivi, t_share *share);
int			divide_sleep(int goal_time, t_share *share, t_indivi *indivi);
void		update_min_count(t_share *share);
int			check_enable_eat(t_indivi *indivi, t_share *share);
void		set_fork(t_share *share, t_indivi *indivi, int fn, int state);
int			check_eat_full(t_share *share);
void		print_eat_time(int number, int eat_count, t_share *s);
void		print_sleep(int number, t_share *share);
void		print_think(int number, t_share *share);
void		print_die(int number, t_share *share);
int			is_end(int ret, t_share *share);
#endif
