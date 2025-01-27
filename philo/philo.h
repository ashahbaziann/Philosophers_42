#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

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
	pthread_t 		thread;
	int				last_eat_time;
	int 			eating_counter;
    int             is_full;
	t_fork          *left_fork;
    t_fork          *right_fork;
    t_data          *data;
} t_philo;

typedef struct s_data
{
    int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
    int             eating_limit;
	int             begin_simulation;
    int             end_simulation;
    int             threads_created;
    t_mtx           data_mtx;
    t_fork          *forks;
    t_philo         *philos;
} t_data;

typedef enum s_attr
{
    INIT,
    DESTROY,
    LOCK,
    UNLOCK,
    JOIN,
    CREATE,
} t_attr;

int		validate_arguments(int argc, char **argv);
long	ft_atoi(char *str);
void	print_error(char *str);
int		ft_strlen(char *str);
int		contains_letters(char *str);
int		is_alpha(int c);
int		init_data(t_data *data, char **argv);
int     mutex_handler(t_mtx *mtx, t_attr attr);
int     thread_handler(pthread_t *thread, t_attr attr, void *(*routine)(void *), void *arg);
void    setter(t_mtx *mtx, int *dest, int src);
int    getter(t_mtx *mtx, int *src);
void    start_simulation(t_data *data);
int is_sim_finished(t_data *data);
int	ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
#endif