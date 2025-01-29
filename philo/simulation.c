#include "philo.h"

static void wait_threads(t_data *data)
{
   while (!getter_int(&data -> data_mtx, &data -> threads_created))
   ;
}


void thinking(t_philo *philo, int help)
{
	long	think;

	if (!help)
		print_state(philo, THINKING);
	if (philo -> data -> philo_num % 2 == 0)
		return ;
	think = philo -> data -> time_to_eat * 2 - philo -> data -> time_to_sleep;
	if (think < 0)
		think = 0;
	accurate_usleep(philo -> data, think * 0.42);
}

static void sleeping(t_philo *philo)
{
	print_state(philo, SLEEPING);
	accurate_usleep(philo -> data, philo -> data -> time_to_sleep);
}
static void eating (t_philo *philo)
{

	mutex_handler(&philo -> left_fork -> mutex, LOCK);
	print_state(philo, TAKEN_LEFT_FORK);
	mutex_handler(&philo->right_fork->mutex, LOCK);
	print_state(philo, TAKEN_RIGHT_FORK);
	setter_long(&philo -> handy_mutex, &philo -> last_eat_time , get_current_time(MS));
	philo -> eating_counter++;
	print_state(philo, EATING);
	accurate_usleep(philo -> data, philo -> data -> time_to_eat);
	if (philo -> data -> eating_limit > 0 && philo -> eating_counter == philo -> data -> eating_limit)
		setter_int(&philo -> handy_mutex, &philo -> is_full, 1);
	mutex_handler(&philo -> right_fork -> mutex, UNLOCK);
	mutex_handler(&philo -> left_fork -> mutex, UNLOCK);

}


void unsynchronize(t_philo *philo)
{
	if (philo -> data -> philo_num % 2 == 0)
	{
		if (philo -> id % 2 == 0)
			accurate_usleep(philo -> data ,30000);
	}
	else
		if (philo -> id % 2)
			thinking(philo, 1);
}
void  *philo_routine(void *routine)
{
	t_philo	*philo;

	philo = (t_philo *)routine;
	wait_threads(philo -> data);
	setter_long(&philo -> handy_mutex, &philo -> last_eat_time, get_current_time(MS));
	count_alive_threads(&philo -> data -> thread_index, &philo -> data->data_mtx);
	unsynchronize(philo);
	while (!is_sim_finished(philo -> data))
	{
		if (philo -> is_full)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo, 0);
	}

    return (NULL);
}
void start_simulation(t_data *data)
{
    int i;

    i = 0;
	if (data -> philo_num == 0)
		return ;
    else if (data -> philo_num == 1)
		thread_handler(&data->philos[0].thread, CREATE, one_philo_routine, &data->philos[0]);
	else
	{
		while (i < data ->philo_num)
		{
			thread_handler(&data->philos[i].thread, CREATE, philo_routine, &data->philos[i]);
			i++;
		}
	}
	thread_handler(&data->monitor, CREATE, monitor_routine, data);
    data -> begin_simulation = get_current_time(MS);
    setter_int(&data -> data_mtx, &data -> threads_created, 1);
    i = 0;
    while (i < data->philo_num)
    {
        thread_handler(&data->philos[i].thread, JOIN, NULL, NULL);
        i++;
    }
	setter_int(&data -> data_mtx, &data -> end_simulation , 1);
	thread_handler(&data -> monitor, JOIN, NULL, NULL);
}
