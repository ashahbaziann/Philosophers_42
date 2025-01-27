#include "philo.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (validate_arguments(argc, argv) == 0)
		return (1);
	if (init_data(&data, argv) < 0)
		return (1);
	start_simulation(&data);
}