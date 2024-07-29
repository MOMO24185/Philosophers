/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:06:00 by melshafi          #+#    #+#             */
/*   Updated: 2024/07/29 13:16:12 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, uint64_t sleep_time, uint64_t timestamp)
{
	uint64_t	current;

	while (1)
	{
		pthread_mutex_lock(&philo->data->time.time_mutex);
		get_timestamp(philo);
		current = philo->data->time.timestamp_ms;
		pthread_mutex_unlock(&philo->data->time.time_mutex);
		if ((current - timestamp >= (sleep_time / 1000)))
			break ;
		usleep(200);
	}
}
