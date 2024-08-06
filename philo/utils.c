/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:06:00 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/06 15:09:24 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, uint64_t sleep_time)
{
	uint64_t	start;

	start = get_timestamp();
	while (philo->data->dead_thread_id == -1)
	{
		if ((get_timestamp() - start >= (sleep_time / 1000)))
			break ;
		usleep(50);
	}
}
