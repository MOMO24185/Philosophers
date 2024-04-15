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

static int	check_forks(t_philo *philo, int ready_to_eat, int next)
{
	pthread_mutex_lock(&philo->fork_mutex);
	if (!philo->fork_flag)
			ready_to_eat++;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->data->philos[next].fork_mutex);
	if (!philo->data->philos[next].fork_flag)
			ready_to_eat++;
	pthread_mutex_unlock(&philo->data->philos[next].fork_mutex);
	return (ready_to_eat);
}

static int	eat(t_philo *philo, int next)
{
	get_last_meal_time(philo);
	pthread_mutex_lock(&philo->time_mutex);
	get_timestamp(philo);
	printf("\033[0;32m%llu %d is eating\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(philo->data->args->time_to_eat);
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork_flag = 0;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->data->philos[next].fork_mutex);
	philo->data->philos[next].fork_flag = 0;
	pthread_mutex_unlock(&philo->data->philos[next].fork_mutex);
	philo_sleep(philo);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	int	ready_to_eat;
	int	next;

	next = philo->philo_num + 1;
	if (next == philo->data->args->num_of_philo)
		next = 0;
	ready_to_eat = 0;
	while (!ready_to_eat)
	{
		ready_to_eat = check_forks(philo, ready_to_eat, next);
		if (ready_to_eat != 2)
			ready_to_eat = 0;
		else
		{
			pthread_mutex_lock(&philo->fork_mutex);
			philo->fork_flag = 1;
			pthread_mutex_unlock(&philo->fork_mutex);
			pthread_mutex_lock(&philo->data->philos[next].fork_mutex);
			philo->data->philos[next].fork_flag = 1;
			pthread_mutex_unlock(&philo->data->philos[next].fork_mutex);
			return (eat(philo, next), 0);
		}
	}
	return (1);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	get_timestamp(philo);
	printf("\033[0;33m%llu %d is sleeping\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(philo->data->args->time_to_sleep);
	philo_think(philo);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	get_timestamp(philo);
	printf("%llu %d is thinking\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->time_mutex);
}
