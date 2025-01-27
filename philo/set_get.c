#include "philo.h"

void setter(t_mtx *mtx, int *dest, int src)
{
    mutex_handler(mtx, LOCK);
    *dest = src;
    mutex_handler(mtx, UNLOCK);
}

int getter(t_mtx *mtx, int *src)
{
    int result;

    mutex_handler(mtx, LOCK);
    result = *src;
    mutex_handler(mtx, UNLOCK);
    return (result);
}

int is_sim_finished(t_data *data)
{
    return (getter(&data -> data_mtx,&data -> end_simulation));
}