/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbazian <ashahbazian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:20:01 by ashahbazian       #+#    #+#             */
/*   Updated: 2025/04/14 18:20:04 by ashahbazian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_arguments(t_data *data, char **argv)
{
	data -> time_to_die = ft_atoi(argv[2]);
	data -> time_to_eat = ft_atoi(argv[3]);
	data -> time_to_sleep = ft_atoi(argv[4]);
	data -> num_philosophers = ft_atoi(argv[1]);
    if (argv[5])
	    data -> eating_limit = ft_atoi(argv[5]);
    else
        data -> eating_limit = -1;
    data -> simulation_on = 0;
    data -> start_time = 0;
}

static void init_mutexes(t_data *data)
{
    mutex_handler(&data->simulation_mutex, INIT);
    mutex_handler(&data->meals_eaten_mutex, INIT);
    mutex_handler(&data->action_mutex, INIT);
}
static int  init_philos(t_data *data)
{
    int i;

    i = 0;
    data -> philos = malloc(sizeof(t_philo) * data->num_philosophers);
	if (!data -> philos)
	{
		free(data->forks);
        error("Allocation failed\n");
		return (-1);
	}
    while (i < data->num_philosophers)
    {
        data->philos[i].id = i + 1;
        data->philos[i].last_meal_time = get_time();
        data->philos[i].meals_eaten = 0;
        data->philos[i].data = data;
        mutex_handler(&data->philos[i].last_meal_time_mutex, INIT);
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
        i++;
    }
    return (0);
}
static int  init_forks(t_data *data)
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
    {
        error("Allocation failed\n");
		return (-1);
    }
    while (i < data->num_philosophers)
    {
        mutex_handler(&data->forks[i], INIT);
        i++;
    }
    return (0);
}

int init_data(t_data *data, char **argv)
{
    init_arguments(data, argv);
    init_mutexes(data);
    if (init_forks(data) < 0)
        return (-1);
    if (init_philos(data) < 0)
        return (-1);
    return (0);
}