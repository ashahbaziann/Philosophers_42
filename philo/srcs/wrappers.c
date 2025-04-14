/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbazian <ashahbazian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:20:46 by ashahbazian       #+#    #+#             */
/*   Updated: 2025/04/14 18:20:47 by ashahbazian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_status(int status, t_attr attr)
{
    if (status != 0)
    {
        if (attr == INIT)
            error("Mutex initialization failed\n");
        else if (attr == DESTROY)
            error("Mutex destruction failed\n");
        else if (attr == LOCK)
            error("Mutex failed locking\n");
        else if (attr == UNLOCK)
            error("Mutex failed unlocking\n");
        return (-1);
    }
    return (0);
}
int    mutex_handler(pthread_mutex_t *mtx, t_attr attr)
{
    if (attr == INIT)
    {
        if (check_status(pthread_mutex_init(mtx, NULL) ,attr) < 0)
            return (-1);
    }
    else if (attr == DESTROY)
    {
        if (check_status(pthread_mutex_destroy(mtx), attr) < 0)
            return (-1);
    }
    else if (attr == LOCK)
    {
        if (check_status(pthread_mutex_lock(mtx), attr) < 0)
            return (-1);
    }
    else if (attr == UNLOCK)
    {
        if (check_status(pthread_mutex_unlock(mtx), attr) < 0)
            return (-1);
    }
    return (0);
}

int thread_handler(pthread_t *thread, t_attr attr, void *(*routine)(void *), void *arg)
{
    if (attr == JOIN)
    {
        if (pthread_join(*thread, NULL) != 0)
        {
            error("Threads failed to join\n");
            return (-1);
        }
    }
    else if (attr == CREATE)
    {
        if (pthread_create(thread, NULL, routine, arg) != 0)
        {
            error("Thread failed to create\n");
            return (-1);
        }
    }
    return (0);
}
