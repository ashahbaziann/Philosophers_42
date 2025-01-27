#include "philo.h"

static void wait_threads(t_data *data)
{
   while (!getter(&data -> data_mtx, &data -> threads_created))
   ;
}
void  *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
   wait_threads(philo -> data);
   
  
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
        mutex_handler(&data -> data_mtx, LOCK);
        printf("Philosopher %d is starting its routine.\n", data ->philos[i].id);
        mutex_handler(&data -> data_mtx, UNLOCK);
        i++;
    }
    data -> begin_simulation = get_current_time();
    setter(&data -> data_mtx, &data -> threads_created, 1);
    i = 0;
    while (i < data->philo_num)
    {
        thread_handler(&data->philos[i].thread, JOIN, NULL, NULL);
        i++;
    }
}