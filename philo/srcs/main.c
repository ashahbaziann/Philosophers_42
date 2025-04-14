/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashahbazian <ashahbazian@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:20:11 by ashahbazian       #+#    #+#             */
/*   Updated: 2025/04/14 18:50:07 by ashahbazian      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data	data;

	if (validate_arguments(argc, argv) == 0)
		return (FAILURE);
    if (init_data(&data, argv) < 0)
        return (FAILURE);
    if (start_simulation(&data) < 0)
        return (FAILURE);
    if (clean(&data) < 0)
        return (FAILURE);
}