/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:42:46 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 17:24:10 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *msg)
{
	printf(RED "Error: %s\n" RESET, msg);
	exit(1);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	smart_sleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	print_msg(t_philo *philo, char *msg)
{
	bool	should_print;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->stop_lock);
	should_print = !philo->data->stop;
	if (should_print)
		printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id,
			msg);
	pthread_mutex_unlock(&philo->data->stop_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
}

bool	should_stop(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->stop_lock);
	stop = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (stop);
}
