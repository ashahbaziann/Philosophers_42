/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbazian <ashahbazian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:20:24 by ashahbazian       #+#    #+#             */
/*   Updated: 2025/04/14 18:48:34 by ashahbazian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int simulation_on(t_data *data)
{
    int res;

    res = 0;
	mutex_handler(&data->simulation_mutex, LOCK);
    if (data->simulation_on == 1)
	{
        res = 1;
	}
	mutex_handler(&data->simulation_mutex, UNLOCK);
	return (res);
}

void display_state(t_philo *philo, t_philo_state state)
{
	long passed;
	
	mutex_handler(&philo->data->action_mutex, LOCK);
	passed = get_time() - philo->data->start_time;
	if ((state == TAKEN_LEFT_FORK || state == TAKEN_RIGHT_FORK) && simulation_on(philo->data))
		printf("%ld %d has taken a fork\n",passed,  philo -> id);
	else if (state == EATING && simulation_on(philo->data))
		printf("%ld %d is eating\n", passed, philo -> id);
	else if (state == THINKING && simulation_on(philo->data))
		printf("%ld %d is thinking\n", passed, philo -> id);
	else if (state == SLEEPING && simulation_on(philo->data))
		printf("%ld %d is sleeping\n", passed, philo -> id);
	else if (state == DIED && simulation_on(philo->data))
		printf("%ld %d died\n", passed, philo -> id);
	mutex_handler(&philo->data->action_mutex, UNLOCK);
}

void create_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philosophers)
    {
        thread_handler(&data->philos[i].thread, CREATE, routine, &data->philos[i]);
        i++;
    }
}
void	wait_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
        thread_handler(&data->philos[i].thread, JOIN, NULL, NULL);
		i++;
	}
}
static int destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (!mutex_handler(&data->forks[i], DESTROY))
			return (1);
		i++;
	}
	mutex_handler(&data->simulation_mutex, DESTROY);
	mutex_handler(&data->meals_eaten_mutex, DESTROY);
	mutex_handler(&data->action_mutex, DESTROY);
	mutex_handler(&data->philos->last_meal_time_mutex, DESTROY);
	return (0);
}
int	clean(t_data *data)
{
	if (!data)
		return (-1);
	destroy_mutexes(data);
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	return (0);
}