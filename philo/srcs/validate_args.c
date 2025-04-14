/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbazian <ashahbazian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:20:38 by ashahbazian       #+#    #+#             */
/*   Updated: 2025/04/14 18:20:40 by ashahbazian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	contains_letters(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (is_alpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(char *str)
{
	int	i;
	int	sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (contains_letters(str) == 1)
		return (-1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	validate_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			if (ft_atoi(argv[i]) < 0)
			{
				error("Invalid arguments\n");
				return (0);
			}
			i++;
		}
		return (1);
	}
	else
		error("Invalid arguments\n");
	return (0);
}