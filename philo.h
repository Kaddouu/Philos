/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilkaddou <ilkaddou@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:17:37 by ilkaddou          #+#    #+#             */
/*   Updated: 2025/02/22 13:26:06 by ilkaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define RED "\033[1;31m"
# define RESET "\033[0m"

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}					t_fork;

typedef struct s_philo
{
	int				id;
	long			meals;
	long			last_meal;
	bool			is_full;
	pthread_mutex_t	meal_lock;
	t_fork			*first;
	t_fork			*second;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_to_eat;
	long			start_time;
	bool			stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	print_lock;
	t_fork			*forks;
	t_philo			*philos;
}					t_data;

void				init_mutexes(t_data *data);
void				init_philos(t_data *data);
void				*philo_routine(void *arg);
void				handle_eating(t_philo *philo);
void				handle_sleeping(t_philo *philo);
void				*monitor_routine(void *arg);
bool				check_philo_death(t_data *data, t_philo *philo);
int					start_simulation(t_data *data);
void				clean_data(t_data *data);
void				error(char *msg);
long				get_time(void);
void				smart_sleep(long ms);
void				print_msg(t_philo *philo, char *msg);
bool				should_stop(t_data *data);
void				ft_parse(t_data *data, char **av);
void				init_data(t_data *data);

#endif