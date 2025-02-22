/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:57:53 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 14:04:10 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		pthread_mutex_destroy(&data->philos[i].meal_lock);
	}
	pthread_mutex_destroy(&data->stop_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(data->philos);
	free(data->forks);
}

int	start_simulation(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monitor;
	int			i;

	threads = malloc(sizeof(pthread_t) * data->philo_count);
	if (!threads)
		return (1);
	data->start_time = get_time();
	i = -1;
	while (++i < data->philo_count)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&threads[i], NULL, philo_routine,
				&data->philos[i]))
			return (1);
		usleep(1000);
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (1);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->philo_count)
		pthread_join(threads[i], NULL);
	free(threads);
	return (0);
}
