/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/03 13:01:10 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*check_death_routine(void *var)
{
	t_philos_data	*philosophers;
	t_philo			*philo;

	philosophers = var;
	while (1)
	{
		printf("%d dead_thread_ID\n", philosophers->dead_thread_id);
		if (philosophers->dead_thread_id >= 0)
			break ;
	}
	philo = &philosophers->philos[philosophers->dead_thread_id];
	printf("\033[0;31m%d dead_thread_ID\n\033[0m", philosophers->dead_thread_id);
	get_timestamp(philo);
	pthread_mutex_lock(&philosophers->death_mutex);
	pthread_mutex_unlock(&philosophers->death_mutex);
	printf("\033[0;31m%ld %d died\n\033[0m",
		philo->data->time.timestamp_ms, philo->philo_num);
	return (NULL);
}

void	*time_routine(void *var)
{
	return (var);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	get_timestamp(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->time_mutex);
		if ((philo->data->args->num_to_eat != 0
				&& philo->meal_counter == philo->data->args->num_to_eat)
				|| philo->data->time.timestamp_ms - philo->last_meal
				< philo->data->args->time_to_die)
			{
			pthread_mutex_unlock(&philo->time_mutex);
			break ;
			}
		pthread_mutex_unlock(&philo->time_mutex);
		philo_eat(*philo);
		usleep(1);
	}
	pthread_mutex_lock(&philo->data_mutex);
	printf("\033[0;31m%d dead philo_num\n\033[0m", philo->philo_num);
	philo->data->dead_thread_id = philo->philo_num;
	pthread_mutex_unlock(&philo->data_mutex);
	return (NULL);
}

int	start_pthreads(t_philo *philos, t_args *args, t_philos_data *philosophers)
{
	int				count;
	struct timeval	start;

	count = -1;
	if (pthread_create(&philosophers->death_thread, NULL, &check_death_routine,
			(void *)&philosophers) != 0)
		return (printf("%s\n", ERR_PTHREAD), free(philos), free(args), 1);
	if (init_mutex(philos, args->num_of_philo))
		return (printf("%s\n", ERR_MUTEX_INIT), 1);
	while (++count < args->num_of_philo)
		create_philo(&philos[count], count, philosophers);
	count = -1;
	gettimeofday(&start, 0);
	philosophers->time.start = start;
	philosophers->time.timestamp_ms = 0;
	while (++count < args->num_of_philo)
	{
		if (philos[count].philo_num == -1)
			return (free(philos), free(args), 1);
		if (pthread_create(&philos[count].thread, NULL, &routine,
				(void *)&philos[count]) != 0)
			return (printf("%s\n", ERR_PTHREAD), free(philos), free(args), 1);
	}
	return (0);
}
