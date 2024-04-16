/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:50:53 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/15 19:00:40 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	check_forks(t_philo *philo, int next)
{
	int ready_to_eat;
	int	reserved;

	ready_to_eat = 0;
	pthread_mutex_lock(&philo->fork_mutex);
	reserved = philo->philo_num;
	if (philo->fork_flag == -1)
	{
		ready_to_eat++;
		philo->fork_flag = reserved;
	}
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->data->philos[next].fork_mutex);
	if (philo->data->philos[next].fork_flag == -1)
	{		
		ready_to_eat++;
		philo->data->philos[next].fork_flag = reserved;
	}
	pthread_mutex_unlock(&philo->data->philos[next].fork_mutex);
	return (ready_to_eat);
}

static int	eat(t_philo *philo, int next)
{
	get_last_meal_time(philo);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_thread_id >= 0)
		return (pthread_mutex_unlock(&philo->data->death_mutex), 0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	get_timestamp(philo);
	printf("\033[0;32m%lu %d is eating\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	philo->meal_counter++;
	usleep(philo->data->args->time_to_eat);
	pthread_mutex_unlock(&philo->time_mutex);
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork_flag = -1;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->data->philos[next].fork_mutex);
	philo->data->philos[next].fork_flag = -1;
	pthread_mutex_unlock(&philo->data->philos[next].fork_mutex);
	return (philo_sleep(philo));
}

int	philo_eat(t_philo *philo)
{
	int	next;

	next = philo->philo_num + 1;
	if (next == philo->data->args->num_of_philo)
		next = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead_thread_id >= 0)
			return (pthread_mutex_unlock(&philo->data->death_mutex), 0);
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (check_forks(philo, next) == 2)
			return (eat(philo, next));
	}
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	if (!check_thread_continue(philo))
		return (0);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_thread_id >= 0)
		return (pthread_mutex_unlock(&philo->data->death_mutex), 0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	get_timestamp(philo);
	printf("\033[0;33m%lu %d is sleeping\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(philo->data->args->time_to_sleep);
	return (1);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	get_timestamp(philo);
	printf("%lu %d is thinking\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->time_mutex);
}
