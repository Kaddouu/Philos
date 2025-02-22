/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:51:59 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 13:32:58 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->stop_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		pthread_mutex_init(&data->philos[i].meal_lock, NULL);
		data->forks[i].id = i;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].is_full = false;
		data->philos[i].data = data;
		data->philos[i].last_meal = 0;
		if (i % 2 == 0)
		{
			data->philos[i].first = &data->forks[i];
			data->philos[i].second = &data->forks[(i + 1)
				% data->philo_count];
		}
		else
		{
			data->philos[i].first = &data->forks[(i + 1)
				% data->philo_count];
			data->philos[i].second = &data->forks[i];
		}
	}
}

void	init_data(t_data *data)
{
	data->stop = false;
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	data->forks = malloc(sizeof(t_fork) * data->philo_count);
	if (!data->philos || !data->forks)
		error("malloc failed");
	init_mutexes(data);
	init_philos(data);
}
