#include "philo.h"

static void wait_threads(t_data *data)
{
   while (!getter(&data -> data_mtx, &data -> threads_created))
   ;
}


static void thinking(t_philo *philo)
{
	print_state(philo, THINKING);
	//accurate_usleep(philo -> data, philo -> data -> )
}

static void sleeping(t_philo *philo)
{
	printf("aint we reaching\n");
	print_state(philo, SLEEPING);
	accurate_usleep(philo -> data, philo -> data -> time_to_sleep);
}
static void eating (t_philo *philo)
{

	//mutex_handler(&philo -> left_fork -> mutex, LOCK);
	printf("Philosopher %d is attempting to take left fork.\n", philo->id);
	mutex_handler(&philo->left_fork->mutex, LOCK);
	printf("Philosopher %d took left fork.\n", philo->id);

	//print_state(philo, TAKEN_LEFT_FORK);
	//mutex_handler(&philo -> right_fork -> mutex, LOCK);
	//print_state(philo, TAKEN_RIGHT_FORK);
	printf("Philosopher %d is attempting to take right fork.\n", philo->id);
	mutex_handler(&philo->right_fork->mutex, LOCK);
	printf("Philosopher %d took right fork.\n", philo->id);
	setter(&philo -> handy_mutex, &philo -> last_eat_time , get_current_time(MS));
	philo -> eating_counter++;
	print_state(philo, EATING);
	accurate_usleep(philo -> data, philo -> data -> time_to_eat);
	mutex_handler(&philo -> right_fork -> mutex, UNLOCK);
	mutex_handler(&philo -> left_fork -> mutex, UNLOCK);

}
void  *philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo -> data);
	while (!is_sim_finished(philo -> data))
	{
		if (philo -> is_full)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}

    return (NULL);
}
void start_simulation(t_data *data)
{
    int i;

    i = 0;
    if (data -> philo_num == 1)
        return ;//to do
    while (i < data ->philo_num)
    {
        thread_handler(&data->philos[i].thread, CREATE, philo_routine, &data->philos[i]);
        // mutex_handler(&data -> data_mtx, LOCK);
        // printf("Philosopher %d is starting its routine.\n", data ->philos[i].id);
        // mutex_handler(&data -> data_mtx, UNLOCK);
        i++;
    }
    data -> begin_simulation = get_current_time(MS);
    setter(&data -> data_mtx, &data -> threads_created, 1);
    i = 0;
    while (i < data->philo_num)
    {
        thread_handler(&data->philos[i].thread, JOIN, NULL, NULL);
        i++;
    }
}
