/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:06:00 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/07 12:19:40 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(uint64_t sleep_time)
{
	uint64_t	start;
	uint64_t	current;

	start = get_timestamp();
	while (1)
	{
		current = get_timestamp();
		if ((current - start >= (sleep_time / 1000)))
			return (1);
		usleep(50);
	}
	return (0);
}
