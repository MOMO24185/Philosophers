/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/15 16:04:21 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*check_death_routine(void *var)
{
	t_philos_data	*philosophers;
	t_philo			*philo;
	int				dead_thread;

	philosophers = var;
	while (1)
	{
		pthread_mutex_lock(&philosophers->death_mutex);
		if (philosophers->dead_thread_id >= 0)
		{
			dead_thread = philosophers->dead_thread_id;
			pthread_mutex_unlock(&philosophers->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosophers->death_mutex);
		usleep(2);
	}
	pthread_mutex_lock(&philosophers->death_mutex);
	philo = &philosophers->philos[dead_thread];
	pthread_mutex_unlock(&philosophers->death_mutex);
	get_timestamp(philo);
	pthread_mutex_lock(&philo->time_mutex);
	while (!philo->data->time.flag)
		;
	philo->data->time.flag = 0;
	printf("\033[0;31m%llu %d died\n\033[0m",
		philo->data->time.timestamp_ms, dead_thread);
	philo->data->time.flag = 1;
	pthread_mutex_unlock(&philo->time_mutex);
	pause();
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
	while (1)
	{
		if (survival_conditions(philo) == 1)
			break ;
		philo_eat(philo);
		usleep(1);
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_thread_id == -1)
		philo->data->dead_thread_id = philo->philo_num;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (NULL);
}

int	start_pthreads(t_philo *philos, t_args *args, t_philos_data *philosophers)
{
	int				count;
	struct timeval	start;

	count = -1;
	if (pthread_create(&philosophers->death_thread, NULL, &check_death_routine,
			(void *)philosophers) != 0)
		return (printf("%s\n", ERR_PTHREAD), free(philos), free(args), 1);
	if (init_mutex(philos, args->num_of_philo))
		return (printf("%s\n", ERR_MUTEX_INIT), 1);
	while (++count < args->num_of_philo)
		create_philo(&philos[count], count, philosophers);
	count = -1;
	gettimeofday(&start, 0);
	philosophers->time.flag = 1;
	philosophers->time.start = start;
	philosophers->time.timestamp_ms = 0;
	while (++count < args->num_of_philo)
	{
		if (pthread_create(&philos[count].thread, NULL, &routine,
				(void *)&philos[count]) != 0 || philos[count].philo_num == -1)
			return (printf("%s\n", ERR_PTHREAD), free(philos), free(args), 1);
	}
	return (0);
}

int	survival_conditions(t_philo *philo)
{
	get_timestamp(philo);
	pthread_mutex_lock(&philo->data_mutex);
	if ((philo->data->args->num_to_eat > 0 && philo->meal_counter >= philo->data->args->num_to_eat)
		|| (philo->data->time.timestamp_ms - philo->last_meal >= philo->data->args->time_to_die))
	{
		return (pthread_mutex_unlock(&philo->data_mutex), 1);
	}
	if (philo->data->dead_thread_id >= 0)
	{
		return (pthread_mutex_unlock(&philo->data_mutex), 1);
	}
	pthread_mutex_unlock(&philo->data_mutex);
	return (0);
}
