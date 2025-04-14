/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbazian <ashahbazian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:19:52 by ashahbazian       #+#    #+#             */
/*   Updated: 2025/04/14 18:19:53 by ashahbazian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_philo_death(t_philo *philo)
{
    long    time;
    
    time = get_time() - philo->last_meal_time;
    if (time >= philo->data->time_to_die)
    {
        display_state(philo, DIED);
        mutex_handler(&philo->data->simulation_mutex, LOCK);
        philo->data->simulation_on = 0;
        mutex_handler(&philo->data->simulation_mutex, UNLOCK);
        return (1);
    }
    return (0);
}

static int  check_all_ate_enough(t_data *data)
{
    int      i;

    i = 0;
    while (i < data->num_philosophers)
    {
        mutex_handler(&data->meals_eaten_mutex, LOCK);
        if(data->philos[i].meals_eaten < data->eating_limit)
        {
            mutex_handler(&data->meals_eaten_mutex, UNLOCK);
            return 0;
        }
        mutex_handler(&data->meals_eaten_mutex, UNLOCK);
        i++;
    }
    return (1);
}

static int does_simulation_end(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->num_philosophers)
    {
        mutex_handler(&data->philos[i].last_meal_time_mutex, LOCK);
        if (check_philo_death(&data->philos[i]))
        {
            mutex_handler(&data->philos[i].last_meal_time_mutex, UNLOCK);
            return (1);
        }
        mutex_handler(&data->philos[i].last_meal_time_mutex, UNLOCK);
        i++;
    }
    return (0);
}

static void    *monitor_routine(void *arg)
{
    t_data *data;

    data = (t_data *)arg;
    while (1)
    {

        if (does_simulation_end(data))
			return (NULL);
        if(data->eating_limit != -1 && check_all_ate_enough(data))
        {
            mutex_handler(&data->simulation_mutex, LOCK);
            data->simulation_on = 0;
            mutex_handler(&data->simulation_mutex, UNLOCK);
            return NULL;
        }
		usleep(1000);
    }
    return (NULL);
}

int start_simulation(t_data *data)
{
    pthread_t monitor_thread;

    data->simulation_on = 1;
    data->start_time = get_time();
    create_philos(data);
    if (data->num_philosophers > 1)
        pthread_create(&monitor_thread, NULL, &monitor_routine, data);
    wait_all_philos(data);
    if (data->num_philosophers > 1)
        pthread_join(monitor_thread, NULL);
    return(0);
}