/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:40:32 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 13:25:37 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */
#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	ft_parse(&data, av);
	init_data(&data);
	if (start_simulation(&data))
	{
		clean_data(&data);
		printf("Error: simulation failed\n");
		return (1);
	}
	clean_data(&data);
	return (0);
}
