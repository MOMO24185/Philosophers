/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/27 11:45:47 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;

	pthread_mutex_lock(&philo->fork_mutex);
	gettimeofday(&philo->time.end, 0);
	philo->time.timestamp_ms = get_time_in_ms(philo->time.start,
			philo->time.end);
	pthread_mutex_unlock(&philo->fork_mutex);

	printf("Timestamp: %ldms Philosopher %d is saying something\n",
		philo->time.timestamp_ms, philo->philo_num);
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
