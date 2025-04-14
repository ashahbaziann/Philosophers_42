/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbazian <ashahbazian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:19:26 by ashahbazian       #+#    #+#             */
/*   Updated: 2025/04/14 18:19:28 by ashahbazian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void eating(t_philo *philo)
{
    mutex_handler(philo->left_fork, LOCK);
    display_state(philo, TAKEN_LEFT_FORK);
    mutex_handler(philo->right_fork, LOCK);
    display_state(philo, TAKEN_RIGHT_FORK);
    mutex_handler(&philo->last_meal_time_mutex, LOCK);
    philo->last_meal_time = get_time();
    mutex_handler(&philo->last_meal_time_mutex, UNLOCK);
    display_state(philo, EATING);
    ft_sleep(philo->data->time_to_eat);
    mutex_handler(&philo->data->meals_eaten_mutex, LOCK);
    philo->meals_eaten++;
    mutex_handler(&philo->data->meals_eaten_mutex, UNLOCK);
    mutex_handler(philo->left_fork, UNLOCK);
    mutex_handler(philo->right_fork, UNLOCK);
}

static void sleeping(t_philo *philo)
{
    display_state(philo, SLEEPING);
    ft_sleep(philo->data->time_to_sleep);
}

static void single_philo(t_philo *philo)
{
    mutex_handler(philo->right_fork, LOCK);
    display_state(philo, TAKEN_RIGHT_FORK);
    ft_sleep(philo->data->time_to_die);
    display_state(philo, DIED);
    philo->data->simulation_on = 0;
    mutex_handler(philo->right_fork, UNLOCK);
    return ;
}
void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    if (philo->data->num_philosophers == 1)
        single_philo(philo);
    if (philo->id % 2 == 0)
        ft_sleep(100);
    while  (simulation_on(philo->data))
    {
        eating(philo);
        sleeping(philo);
        display_state(philo, THINKING);
    }
    return (NULL);
}
