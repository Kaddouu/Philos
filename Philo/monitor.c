/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:57:56 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 14:27:38 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_philo_death(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (!philo->is_full && get_time() - philo->last_meal > data->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_lock(&data->print_lock);
		printf("%ld %d died\n", get_time() - data->start_time, philo->id);
		pthread_mutex_lock(&data->stop_lock);
		data->stop = true;
		pthread_mutex_unlock(&data->stop_lock);
		pthread_mutex_unlock(&data->print_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (false);
}

bool	check_all_philos_full(t_data *data)
{
	int	index;
	int	full_philos;

	index = -1;
	full_philos = 0;
	while (++index < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[index].meal_lock);
		if (data->philos[index].is_full)
			full_philos++;
		pthread_mutex_unlock(&data->philos[index].meal_lock);
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
		usleep(5000);
	}
	return (NULL);
}
