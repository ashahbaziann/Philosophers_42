#include "philo.h"

void print_state(t_philo *philo, t_philo_state state)
{
	long passed;

	if (philo -> is_full)
	passed = get_current_time(MS) - philo->data->begin_simulation;
		return ;
	mutex_handler(&philo -> data->data_mtx, LOCK);
	if (!is_sim_finished(philo -> data) && (state == TAKEN_LEFT_FORK || state == TAKEN_RIGHT_FORK))
		printf("%ld %d has taken a fork\n", passed, philo -> id);
	else if (state == EATING && !is_sim_finished(philo -> data))
		printf("%ld %d is eating\n", passed, philo -> id);
	else if (state == THINKING && !is_sim_finished(philo -> data))
		printf("%ld %d is taking\n", passed, philo -> id);
	else if (state == SLEEPING && !is_sim_finished(philo -> data))
		printf("%ld %d is sleeping\n", passed, philo -> id);
	else if (state == DIED && !is_sim_finished(philo -> data))
		printf("%ld %d died\n", passed, philo -> id);
	mutex_handler(&philo -> data->data_mtx, UNLOCK);
}
