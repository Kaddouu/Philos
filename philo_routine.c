/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:57:42 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 17:17:29 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	should_continue_eating(t_philo *philo)
{
	t_data	*data;
	bool	continue_eating;

	data = philo->data;
	pthread_mutex_lock(&philo->meal_lock);
	if (!philo->is_full && (data->meals_to_eat == -1
			|| philo->meals < data->meals_to_eat))
		continue_eating = true;
	else
		continue_eating = false;
	pthread_mutex_unlock(&philo->meal_lock);
	return (continue_eating);
}

void	handle_one_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->first->mutex);
	print_msg(philo, "has taken a fork");
	smart_sleep(data->time_to_die);
	pthread_mutex_unlock(&philo->first->mutex);
	return ;
}

void	handle_eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (!should_continue_eating(philo))
		return ;
	pthread_mutex_lock(&philo->first->mutex);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second->mutex);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals++;
	if (data->meals_to_eat != -1 && philo->meals >= data->meals_to_eat)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->meal_lock);
	smart_sleep(data->time_to_eat);
	pthread_mutex_unlock(&philo->first->mutex);
	pthread_mutex_unlock(&philo->second->mutex);
}

void	handle_sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep);
	print_msg(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		handle_one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!should_stop(philo->data))
	{
		if (!should_continue_eating(philo))
			break ;
		handle_eating(philo);
		if (should_stop(philo->data))
			break ;
		handle_sleeping(philo);
	}
	return (NULL);
}
