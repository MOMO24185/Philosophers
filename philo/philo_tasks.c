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

int	philo_eat(t_philo *philo)
{
	int	next;

	if (philo->philo_num + 1 == philo->data->args->num_of_philo)
		next = 0;
	else
		next = philo->philo_num + 1;
	pthread_mutex_lock(&philo->fork_mutex);
	if (!philo->fork_flag && !philo->data->philos[next].fork_flag)
	{
		philo->fork_flag = 1;
		philo->data->philos[next].fork_flag = 1;
		pthread_mutex_unlock(&philo->fork_mutex);
		usleep(philo->data->args->time_to_eat);
		get_timestamp(philo);
		get_last_meal_time(philo);
		pthread_mutex_lock(&philo->data_mutex);
		printf("\033[0;32m%llu %d is eating\n\033[0m",
			philo->data->time.timestamp_ms, philo->philo_num);
		pthread_mutex_unlock(&philo->data_mutex);
		pthread_mutex_lock(&philo->fork_mutex);
		philo->fork_flag = 0;
		philo->data->philos[next].fork_flag = 0;
		pthread_mutex_unlock(&philo->fork_mutex);
		philo_sleep(philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->fork_mutex);
	return (1);
}

void	philo_sleep(t_philo *philo)
{
	if ((philo->data->args->num_to_eat > 0 && philo->meal_counter
			>= philo->data->args->num_to_eat))
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead_thread_id == -1)
			philo->data->dead_thread_id = philo->philo_num;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	get_timestamp(philo);
	pthread_mutex_lock(&philo->data_mutex);
	philo->meal_counter++;
	printf("\033[0;33m%llu %d is sleeping\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->data_mutex);
	usleep(philo->data->args->time_to_sleep);
	philo_think(philo);
}

void	philo_think(t_philo *philo)
{
	get_timestamp(philo);
	pthread_mutex_lock(&philo->data_mutex);
	printf("%llu %d is thinking\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->data_mutex);
}
