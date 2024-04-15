/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:30 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/15 16:18:59 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	get_timestamp(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	while (!philo->data->time.flag)
		;
	philo->data->time.flag = 0;
	gettimeofday(&philo->data->time.end, 0);
	philo->data->time.timestamp_ms = get_time_in_ms(philo->data->time.start,
			philo->data->time.end);
	philo->data->time.flag = 1;
	pthread_mutex_unlock(&philo->time_mutex);
}

void	get_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	gettimeofday(&philo->data->time.end, 0);
	philo->last_meal = get_time_in_ms(philo->data->time.start,
			philo->data->time.end);
	pthread_mutex_unlock(&philo->time_mutex);
}

unsigned long	get_time_in_ms(struct timeval start, struct timeval end)
{
	return (((end.tv_sec * 1000) + end.tv_usec / 1000) - ((
				start.tv_sec * 1000) + start.tv_usec / 1000));
}
