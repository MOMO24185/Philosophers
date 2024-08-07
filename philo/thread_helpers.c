/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:30 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/07 13:00:44 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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
	pthread_mutex_lock(&philo->data->eater);
	if (philo->data->they_ate == philo->data->args->num_of_philo)
		return (pthread_mutex_unlock(&philo->data->eater), 0);
	pthread_mutex_unlock(&philo->data->eater);
	return (1);
}
