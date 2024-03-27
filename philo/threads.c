/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/27 12:49:26 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	philo_eat(*philo);
	return (NULL);
}

int	start_pthreads(t_philo *philos, t_args *args, t_philos_data philosophers,
	struct timeval start)
{
	int	count;

	count = -1;
	while (++count < args->num_of_philo)
	{
		philos[count] = create_philo(count, start, &philosophers);
		if (philos[count].philo_num == -1)
			return (free(philos), free(args), 1);
		if (pthread_create(&philos[count].thread, NULL, &routine,
				(void *)&philos[count]) != 0)
			return (printf("%s\n", ERR_PTHREAD), free(philos), free(args), 1);
	}
	return (0);
}
