/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:06:00 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/06 16:44:58 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_philo *philo, uint64_t sleep_time)
{
	uint64_t	start;
	uint64_t	current;

	start = get_timestamp();
	while (1)
	{
		current = get_timestamp();
		if ((current - start >= (sleep_time / 1000)))
			return (1);
		if ((current - philo->last_meal >= (philo->data->args->time_to_die
					/ 1000)))
			return (0);
		usleep(50);
	}
	return (0);
}
