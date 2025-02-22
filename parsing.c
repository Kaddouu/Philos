/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:37:22 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 13:23:57 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static long	ft_atol(const char *nptr)
{
	long	nbr;
	long	prev;

	nbr = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			error("No negative values");
		if (*nptr == '+')
			nptr++;
	}
	if (!ft_isdigit(*nptr))
		error("Not a digit");
	while (*nptr && ft_isdigit(*nptr))
	{
		prev = nbr;
		nbr = nbr * 10 + (*nptr++ - '0');
		if (nbr < prev || nbr > INT_MAX)
			error("Number overflow");
	}
	return (nbr);
}

void	ft_parse(t_data *data, char **av)
{
	data->philo_count = ft_atol(av[1]);
	if (data->philo_count < 1)
		error("Not enough philos");
	data->time_to_die = ft_atol(av[2]);
	if (data->time_to_die < 0)
		error("Invalid time to die");
	data->time_to_eat = ft_atol(av[3]);
	if (data->time_to_eat < 0)
		error("Invalid time to eat");
	data->time_to_sleep = ft_atol(av[4]);
	if (data->time_to_sleep < 0)
		error("Invalid time to sleep");
	if (av[5])
	{
		data->meals_to_eat = ft_atol(av[5]);
		if (data->meals_to_eat < 0)
			error("Invalid number of meals");
	}
	else
		data->meals_to_eat = -1;
}
