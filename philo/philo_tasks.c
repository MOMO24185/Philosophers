/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:50:53 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/03 13:00:01 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	philo_eat(t_philo philo)
{
	int	next;

	if (philo.philo_num + 1 == philo.data->args->num_of_philo)
		next = 0;
	else
		next = philo.philo_num + 1;
	if (!philo.fork_flag && !philo.data->philos[next].fork_flag)
	{
		pthread_mutex_lock(&philo.fork_mutex);
		philo.fork_flag = 1;
		philo.data->philos[next].fork_flag = 1;
		pthread_mutex_unlock(&philo.fork_mutex);
		get_timestamp(&philo, &philo.data->time.timestamp_ms);
		printf("\033[0;32m%ld %d is eating\n\033[0m",
			philo.data->time.timestamp_ms, philo.philo_num);
		usleep(philo.data->args->time_to_eat);
		get_timestamp(&philo, &philo.last_meal);
		pthread_mutex_lock(&philo.fork_mutex);
		philo.fork_flag = 0;
		philo.data->philos[next].fork_flag = 0;
		pthread_mutex_unlock(&philo.fork_mutex);
		philo_sleep(philo);
		return (0);
	}
	return (1);
}

void	philo_sleep(t_philo philo)
{
	philo.meal_counter++;
	if (philo.meal_counter == philo.data->args->num_to_eat)
		philo.data->dead_thread_id = philo.philo_num;
	get_timestamp(&philo, &philo.data->time.timestamp_ms);
	printf("\033[0;33m%ld %d is sleeping\n\033[0m",
		philo.data->time.timestamp_ms, philo.philo_num);
	usleep(philo.data->args->time_to_sleep);
	philo_think(philo);
}

void	philo_think(t_philo philo)
{
	get_timestamp(&philo, &philo.data->time.timestamp_ms);
	printf("%ld %d is thinking\n\033[0m",
		philo.data->time.timestamp_ms, philo.philo_num);
}
