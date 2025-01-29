#include "philo.h"

void count_alive_threads(long *thread_count, t_mtx *mtx)
{
    mutex_handler(mtx, LOCK);
    (*thread_count)++;
    mutex_handler(mtx, UNLOCK);
}
static int threads_alive(t_mtx *mtx,long *thread_index, long philo_num)
{
    int result;

    result = 0;
    mutex_handler(mtx, LOCK);
    if (philo_num == *thread_index)
        result = 1;
    mutex_handler(mtx, UNLOCK);
    return (result);
}

static int is_dead(t_philo *philo)
{
    long passed;

    if (getter_int(&philo -> handy_mutex, &philo -> is_full))
        return (0);
    passed = get_current_time(MS) - getter_long(&philo -> handy_mutex,&philo ->last_eat_time);
    if (passed > (philo -> data -> time_to_die / 1000))
        return (1);
    return (0);
}
void *monitor_routine(void *routine)
{
    t_data *data;
    int i;

    data = (t_data *)routine;
    i = 0;

    while(!threads_alive(&data -> data_mtx, &data -> thread_index ,data-> philo_num))
        ;
    while (!is_sim_finished(data))
    {
        i = 0;
        while(i < data -> philo_num && !is_sim_finished(data))
        {
            if (is_dead(data->philos + i))
            {
                print_state(data -> philos + i, DIED);////
                setter_int(&data->data_mtx, &data -> end_simulation, 1);
            }
            i++;
        }
    }
    return (NULL);
}

void *one_philo_routine(void *routine)
{
    t_philo *philo;

    philo = (t_philo *)routine;
    while (!getter_int(&philo -> data -> data_mtx, &philo -> data -> threads_created))
     ;
    setter_long(&philo -> handy_mutex, &philo -> last_eat_time, get_current_time(MS));
	count_alive_threads(&philo -> data -> thread_index, &philo -> data->data_mtx);
    print_state(philo, TAKEN_LEFT_FORK);
    while (!is_sim_finished(philo -> data))
        accurate_usleep(philo -> data, 200);
    return (NULL);
}