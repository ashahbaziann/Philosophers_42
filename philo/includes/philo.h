#ifndef PHILO_H
# define PHILO_H

# define FAILURE 1

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
    int				id;
    int             meals_eaten;
    long            last_meal_time;
	t_data			*data;
    pthread_t       thread;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
	pthread_mutex_t	last_meal_time_mutex;
}   t_philo;


typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philosophers;
	int				eating_limit;
	int				simulation_on;
	long			start_time;
	t_philo         *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t	simulation_mutex;
    pthread_mutex_t meals_eaten_mutex;
	pthread_mutex_t	action_mutex;
}	t_data;


typedef enum e_philo_state
{
	EATING,
	THINKING,
	SLEEPING,
	DIED,
	TAKEN_LEFT_FORK,
	TAKEN_RIGHT_FORK,
} t_philo_state;


typedef enum e_attr
{
    INIT,
    DESTROY,
    LOCK,
    UNLOCK,
    JOIN,
    CREATE,
} t_attr;


//validate
int		validate_arguments(int argc, char **argv);

//init
int		init_data(t_data *data, char **argv);

//utils
int		is_alpha(int c);
void	error(char *str);
long	ft_atoi(char *str);
long	get_time(void);
void	ft_sleep(long int ms);

//utils1
int		simulation_on(t_data *data);
void	display_state(t_philo *philo, t_philo_state state);
void	create_philos(t_data *data);
void	wait_all_philos(t_data *data);
int		clean(t_data *data);

//simulation
int		start_simulation(t_data *data);

//routine
void	*routine(void *arg);


//wrappers
int		mutex_handler(pthread_mutex_t *mtx, t_attr attr);
int		thread_handler(pthread_t *thread, t_attr attr, void *(*routine)(void *), void *arg);

#endif