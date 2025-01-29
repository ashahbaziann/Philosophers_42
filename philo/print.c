#include "philo.h"

void print_state(t_philo *philo, t_philo_state state)
{
	long passed;

	passed = get_current_time(MS) - philo->data->begin_simulation;
	if (philo -> is_full)
		return ;
	mutex_handler(&philo -> data->print_mtx, LOCK);
	if ((state == TAKEN_LEFT_FORK || state == TAKEN_RIGHT_FORK) && !is_sim_finished(philo->data))
		printf("%ld %d has taken a fork\n",passed,  philo -> id);
	else if (state == EATING && !is_sim_finished(philo->data))
		printf("%ld %d is eating\n", passed, philo -> id);
	else if (state == THINKING && !is_sim_finished(philo->data))
		printf("%ld %d is thinking\n", passed, philo -> id);
	else if (state == SLEEPING && !is_sim_finished(philo->data))
		printf("%ld %d is sleeping\n", passed, philo -> id);
	else if (state == DIED && !is_sim_finished(philo->data))
		printf("%ld %d died\n", passed, philo -> id);
	mutex_handler(&philo -> data->print_mtx, UNLOCK);
}
