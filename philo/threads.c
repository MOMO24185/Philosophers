/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/27 13:41:06 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*check_death_routine(void *var)
{
	t_philos_data	*philosophers;
	t_philo			philo;

	philosophers = var;
	while (1)
	{
		pthread_mutex_lock(&philosophers->death_mutex);
		if (philosophers->dead_thread_id != 0)
			break ;
		pthread_mutex_unlock(&philosophers->death_mutex);
	}
	philo = philosophers->philos[philosophers->dead_thread_id];
	get_timestamp(&philo, &philo.time.timestamp_ms);
	printf("\033[0;31m%ld %d died\n\033[0m",
		philo.time.timestamp_ms, philo.philo_num);
	return (NULL);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	get_timestamp(philo, &philo->time.timestamp_ms);
	while (philo->time.timestamp_ms < philo->data->args->time_to_die)
		philo_eat(*philo);
	pthread_mutex_lock(&philo->fork_mutex);
	philo->data->dead_thread_id = philo->philo_num;
	pthread_mutex_unlock(&philo->fork_mutex);
	return (NULL);
}

int	start_pthreads(t_philo *philos, t_args *args, t_philos_data philosophers)
{
	int				count;
	struct timeval	start;

	count = -1;
	if (pthread_create(&philosophers.death_thread, NULL, &check_death_routine,
			(void *)&philosophers) != 0)
		return (printf("%s\n", ERR_PTHREAD), free(philos), free(args), 1);
	gettimeofday(&start, 0);
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
