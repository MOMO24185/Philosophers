/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:50:53 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/17 14:40:37 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"



static int	eat(t_philo *philo, int next)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_thread_id >= 0)
		return (pthread_mutex_unlock(&philo->data->death_mutex), 0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	get_timestamp(philo);
	philo->last_meal = philo->data->time.timestamp_ms;
	printf("\033[0;32mTIMESTAMP[%luMS] PHILOSOPHER[%d] IS EATING\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->time_mutex);
	pthread_mutex_lock(&philo->data_mutex);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->data_mutex);
	usleep(philo->data->args->time_to_eat);
	unlock_forks(philo, next);
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
		else
			unlock_forks(philo, next);
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
	printf("\033[0;33mTIMESTAMP[%luMS] PHILOSOPHER[%d] IS SLEEPING\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(philo->data->args->time_to_sleep);
	return (1);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_thread_id >= 0)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->time_mutex);
	get_timestamp(philo);
	printf("TIMESTAMP[%luMS] PHILOSOPHER[%d] IS THINKING\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	pthread_mutex_unlock(&philo->time_mutex);
}
