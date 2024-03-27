/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:30 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/27 13:40:16 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	get_timestamp(t_philo *philo, unsigned long *timestamp)
{
	pthread_mutex_lock(&philo->fork_mutex);
	gettimeofday(&philo->time.end, 0);
	*timestamp = get_time_in_ms(philo->time.start,
			philo->time.end);
	pthread_mutex_unlock(&philo->fork_mutex);
}

unsigned long	get_time_in_ms(struct timeval start, struct timeval end)
{
	return (((end.tv_sec * 1000000) + end.tv_usec) - ((
				start.tv_sec * 1000000) + start.tv_usec));
}
