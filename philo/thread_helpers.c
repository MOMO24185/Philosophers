/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:30 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/06 14:23:08 by melshafi         ###   ########.fr       */
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

int	check_forks(t_philo *og_philo, t_philo *philo, int reserved)
{
	while (1)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		if (philo->fork_flag == -1 || philo->fork_flag == reserved)
		{
			if (philo->fork_flag == -1)
			{
				philo->fork_flag = reserved;
				pthread_mutex_unlock(&philo->fork_mutex);
				print_status(og_philo, "\033[1;36mHAS TAKEN A FORK\033[0m", 0);
			}
			else
				pthread_mutex_unlock(&philo->fork_mutex);
			break ;
		}
		else
			pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead_thread_id >= 0)
			return (pthread_mutex_unlock(&philo->data->death_mutex), 0);
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
	return (1);
}

long long	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
	{
		printf("%s\n", ERR_TIME);
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_thread_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->they_ate == philo->data->args->num_of_philo)
		return (pthread_mutex_unlock(&philo->data->death_mutex), 0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (1);
}
