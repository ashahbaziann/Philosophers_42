#include "philo.h"

static void give_forks(t_data *data, t_philo *philo, int i)
{
    if (i == data->philo_num - 1)
    {
        philo->right_fork = &data->forks[i];
        philo->left_fork = &data->forks[0];
    //    printf("Philosopher %d took fork %ld (left) and fork %ld (right)\n", 
    //            philo->id, 
    //            philo->left_fork - data->forks, 
    //            philo->right_fork - data->forks);
    }
    else
    {
        philo->left_fork = &data->forks[i];
        philo->right_fork = &data->forks[(i + 1) % data->philo_num];
        // printf("Philosopher %d took fork %ld (left) and fork %ld (right)\n", 
        //        philo->id, 
        //        philo->left_fork - data->forks, 
        //        philo->right_fork - data->forks);
    }
}
static void init_philos(t_data *data)
{
	int i;
    t_philo *philo;

	i = 0;
	while (i < data -> philo_num)
	{
        philo = data -> philos + i;
		philo ->id = i + 1;
		philo->last_eat_time = 0;
		philo->eating_counter = 0;
        philo->data = data;
        philo->is_full = 0;
        give_forks(data, philo, i);
		i++;
	}
}


static void init_arguments(t_data *data, char **argv)
{
    int	i;

	i = 1; 
	data -> philo_num = ft_atoi(argv[i]);
	data -> time_to_die = ft_atoi(argv[++i]);
	data -> time_to_eat = ft_atoi(argv[++i]);
	data -> time_to_sleep = ft_atoi(argv[++i]);
    if (argv[5])
	    data -> eating_limit = ft_atoi(argv[++i]);
    else
        data -> eating_limit = -1;
    data -> begin_simulation = 0;
    data -> end_simulation = 0;
    data -> threads_created = 0;
}

int	init_data(t_data *data, char **argv)
{
    int i;

    i = 0;
    init_arguments(data, argv);
	data -> forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!(data -> forks))
		return (-1);
	data -> philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!(data -> philos))
	{
		free(data -> forks);
		return (-1);
	}
    while (i < data -> philo_num)
    {
        mutex_handler(&data -> forks[i].mutex, INIT);// free  if -1
        i++;
    }
    mutex_handler(&data -> data_mtx, INIT);
	init_philos(data);
	return (0);
}