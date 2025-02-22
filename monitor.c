/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:57:56 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 17:40:33 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo_death(t_data *data, t_philo *philo)
{
	long	last_meal_time;
	bool	is_full;

	pthread_mutex_lock(&philo->meal_lock);
	last_meal_time = philo->last_meal;
	is_full = philo->is_full;
	pthread_mutex_unlock(&philo->meal_lock);
	if (!is_full && get_time() - last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_lock);
		pthread_mutex_lock(&data->stop_lock);
		if (!data->stop)
		{
			data->stop = true;
			printf("%ld %d died\n", get_time() - data->start_time, philo->id);
		}
		pthread_mutex_unlock(&data->stop_lock);
		pthread_mutex_unlock(&data->print_lock);
		return (true);
	}
	return (false);
}

bool	check_all_philos_full(t_data *data)
{
	int		index;
	int		full_philos;
	bool	is_full;

	index = -1;
	full_philos = 0;
	while (++index < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[index].meal_lock);
		is_full = data->philos[index].is_full;
		pthread_mutex_unlock(&data->philos[index].meal_lock);
		if (is_full)
			full_philos++;
	}
	if (data->meals_to_eat != -1 && full_philos == data->philo_count)
	{
		pthread_mutex_lock(&data->stop_lock);
		data->stop = true;
		pthread_mutex_unlock(&data->stop_lock);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		index;

	data = (t_data *)arg;
	while (!should_stop(data))
	{
		index = -1;
		while (++index < data->philo_count)
		{
			if (check_philo_death(data, &data->philos[index]))
				return (NULL);
		}
		if (check_all_philos_full(data))
			return (NULL);
		usleep(10);
	}
	return (NULL);
}
