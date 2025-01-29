#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef pthread_mutex_t t_mtx;

typedef struct s_data t_data;

typedef struct s_fork
{
    t_mtx   mutex;
    int     mutex_id;
} t_fork;

typedef struct s_philo
{
	int				id;
	long			last_eat_time;
	long 			eating_counter;
    int             is_full;
	pthread_t 		thread;
	t_mtx			handy_mutex;//last eat
	t_fork          *left_fork;
    t_fork          *right_fork;
    t_data          *data;
} t_philo;

typedef struct s_data
{
    long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
    long            eating_limit;
	long            begin_simulation;
    int            	end_simulation;
    int             threads_created;
	long				thread_index;
	pthread_t		monitor;
    t_mtx           data_mtx;
	t_mtx			print_mtx;
    t_fork          *forks;
    t_philo         *philos;
} t_data;

typedef enum e_attr
{
    INIT,
    DESTROY,
    LOCK,
    UNLOCK,
    JOIN,
    CREATE,
} t_attr;

typedef enum e_time_unit
{
	SC ,
	MS ,
	US ,
} t_time_unit;

typedef enum e_philo_state
{
	EATING,
	THINKING,
	SLEEPING,
	DIED,
	TAKEN_LEFT_FORK,
	TAKEN_RIGHT_FORK,
} t_philo_state;

int		validate_arguments(int argc, char **argv);
long	ft_atoi(char *str);
void	print_error(char *str);
int		ft_strlen(char *str);
int		contains_letters(char *str);
int		is_alpha(int c);
int		init_data(t_data *data, char **argv);
int     mutex_handler(t_mtx *mtx, t_attr attr);
int     thread_handler(pthread_t *thread, t_attr attr, void *(*routine)(void *), void *arg);
void	setter_int(t_mtx *mtx, int *dest, int src);
int		getter_int(t_mtx *mtx, int *src);
void	setter_long(t_mtx *mtx, long *dest, long src);
long	getter_long(t_mtx *mtx, long *src);
void    start_simulation(t_data *data);
int		is_sim_finished(t_data *data);
void	accurate_usleep(t_data *data, long duration);
long	get_current_time(t_time_unit unit);

void print_state(t_philo *philo, t_philo_state state);

//monitor_routine
void *monitor_routine(void *routine);
void count_alive_threads(long *thread_count, t_mtx *mtx);
void *one_philo_routine(void *routine);



void thinking(t_philo *philo, int help);

void unsynchronize(t_philo *philo);
#endif
