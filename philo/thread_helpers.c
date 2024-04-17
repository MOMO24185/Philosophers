/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:30 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/17 14:40:53 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	unlock_forks(t_philo *philo, int next)
{
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork_flag = -1;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->data->philos[next].fork_mutex);
	philo->data->philos[next].fork_flag = -1;
	pthread_mutex_unlock(&philo->data->philos[next].fork_mutex);
}

int	check_forks(t_philo *philo, int next)
{
	int	ready_to_eat;
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

void	get_timestamp(t_philo *philo)
{
	if (gettimeofday(&philo->data->time.end, 0))
	{
		printf("%s\n", ERR_TIME);
		return ;
	}
	philo->data->time.timestamp_ms = get_time_in_ms(philo->data->time.start,
			philo->data->time.end);
}

unsigned long	get_time_in_ms(struct timeval start, struct timeval end)
{
	return (((end.tv_sec * 1000) + end.tv_usec / 1000) - ((
				start.tv_sec * 1000) + start.tv_usec / 1000));
}
