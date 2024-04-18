/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:50:53 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/18 18:21:29 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	eat(t_philo *philo, int next)
{
	uint64_t	timestamp;

	if (!print_status(philo, "\033[1;32mIS EATING\033[0m", 1))
		return (0);
	pthread_mutex_lock(&philo->data->time.time_mutex);
	timestamp = philo->data->time.timestamp_ms;
	pthread_mutex_unlock(&philo->data->time.time_mutex);
	pthread_mutex_lock(&philo->data_mutex);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->data_mutex);
	ft_usleep(philo, philo->data->args->time_to_eat, timestamp);
	unlock_forks(philo, next);
	return (philo_sleep(philo));
}

int	philo_eat(t_philo *philo)
{
	int	next;

	next = philo->philo_num + 1;
	if (next == philo->data->args->num_of_philo)
		next = 0;
	if (check_forks(philo, philo->philo_num)
		&& check_forks(&philo->data->philos[next], next))
		return (eat(philo, next));
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	uint64_t	timestamp;

	if (!print_status(philo, "\033[1;33mIS SLEEPING\033[0m", 0))
		return (0);
	pthread_mutex_lock(&philo->data->time.time_mutex);
	timestamp = philo->data->time.timestamp_ms;
	pthread_mutex_unlock(&philo->data->time.time_mutex);
	ft_usleep(philo, philo->data->args->time_to_sleep, timestamp);
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (!print_status(philo, "\033[1;37mIS THINKING\033[0m", 0))
		return (0);
	return (1);
}

int	print_status(t_philo *philo, char *msg, int is_eating)
{
	pthread_mutex_lock(&philo->data->time.time_mutex);
	get_timestamp(philo);
	if (!philo->data->time.stop_printing
		&& check_thread_continue(philo))
	{
		printf("TIMESTAMP[\033[1;37m%llu\033[0m]ms",
			philo->data->time.timestamp_ms);
		printf(" THREAD[\033[1;37m%d\033[0m] ", philo->philo_num);
		printf("%s\n\033[0m", msg);
		if (is_eating)
			philo->last_meal = philo->data->time.timestamp_ms;
	}
	else
		return (pthread_mutex_unlock(&philo->data->time.time_mutex), 0);
	pthread_mutex_unlock(&philo->data->time.time_mutex);
	return (1);
}
