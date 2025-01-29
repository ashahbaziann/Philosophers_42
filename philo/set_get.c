#include "philo.h"

void setter_int(t_mtx *mtx, int *dest, int src)
{
    mutex_handler(mtx, LOCK);
    *dest = src;
    mutex_handler(mtx, UNLOCK);
}

int getter_int(t_mtx *mtx, int *src)
{
    int result;

    mutex_handler(mtx, LOCK);
    result = *src;
    mutex_handler(mtx, UNLOCK);
    return (result);
}

void setter_long(t_mtx *mtx, long *dest, long src)
{
    mutex_handler(mtx, LOCK);
    *dest = src;
    mutex_handler(mtx, UNLOCK);
}

long getter_long(t_mtx *mtx, long *src)
{
    long result;

    mutex_handler(mtx, LOCK);
    result = *src;
    mutex_handler(mtx, UNLOCK);
    return (result);
}

int is_sim_finished(t_data *data)
{
    return (getter_int(&data -> data_mtx, &data -> end_simulation));
}
