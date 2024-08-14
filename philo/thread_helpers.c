/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:30 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/14 16:58:52 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	lock_forks(t_philo *philo, int left, int right)
{
	if (philo->philo_num % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		pthread_mutex_lock(&philo->data->forks[left]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		pthread_mutex_lock(&philo->data->forks[right]);
	}
	print_status(philo, "\033[1;36mHAS TAKEN A FORK\033[0m", 0);
	print_status(philo, "\033[1;36mHAS TAKEN A FORK\033[0m", 0);
	philo->data->philos[left].fork_taken = 1;
	philo->data->philos[right].fork_taken = 1;
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

int	check_death_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->dead_thread_id != -1)
		return (pthread_mutex_unlock(&philo->data->death), 0);
	pthread_mutex_unlock(&philo->data->death);
	return (1);
}

int	check_thread_continue(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eater);
	if (philo->data->they_ate == philo->data->args->num_of_philo)
	{
		pthread_mutex_lock(&philo->data->death);
		philo->data->dead_thread_id = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (pthread_mutex_unlock(&philo->data->eater), 0);
	}
	pthread_mutex_unlock(&philo->data->eater);
	return (1);
}
