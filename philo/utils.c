#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

int	is_alpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

long	get_current_time(t_time_unit unit)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() failed\n", 22);
	if (unit == SC)
		return (time.tv_sec + time.tv_usec / 1e6);
	else if (unit == MS)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	else if (unit == US)
		return (time.tv_sec * 1000000 + time.tv_usec);
	else
		write(2, "Mistyped input\n", 15);
	return (-1);
}

void	accurate_usleep(t_data *data, long duration)
{
	long	start;
	long	passed;
	long	rest;

	start = get_current_time(US);
	while ((get_current_time(US) - start) < duration)
	{
		if(is_sim_finished(data))
			break ;
		passed = get_current_time(US) - start;
		rest = duration - passed;
		if (rest > 1e3)
			usleep (rest / 2);
		else
			while (get_current_time(US) - start < duration)
				;
	}
}
