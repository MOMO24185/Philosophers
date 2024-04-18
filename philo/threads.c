/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/18 15:17:17 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_thread_id == -1)
	{
		philo->data->dead_thread_id = philo->philo_num;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->time.time_mutex);
		philo->data->time.stop_printing = 1;
		get_timestamp(philo);
		printf("TIMESTAMP[\033[1;37m%llu\033[0m]ms ",
			philo->data->time.timestamp_ms);
		printf("THREAD[\033[1;37m%d\033[0m] ", philo->philo_num);
		printf("\033[1;31mIS DEAD\n\033[0m");
		pthread_mutex_unlock(&philo->data->time.time_mutex);
	}
	else
		pthread_mutex_unlock(&philo->data->death_mutex);
}

void	*time_routine(void *var)
{
	t_philo	*philo;
	int		value;

	philo = var;
	value = survival_conditions(philo);
	while (!value)
		value = survival_conditions(philo);
	if (value == 1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->they_ate++;
		pthread_mutex_unlock(&philo->data->death_mutex);
	}
	if (value == 2)
		check_death(philo);
	return ((void *)0);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	if (philo->philo_num % 2 == 0)
		usleep(philo->data->args->time_to_eat);
	while (1)
	{
		if (check_thread_continue(philo) && philo_eat(philo))
		{
			if (!philo_think(philo))
				break ;
		}
		else
			break ;
	}
	return ((void *)0);
}

int	start_pthreads(t_philo *philos, t_args *args, t_philos_data *philosophers)
{
	int				count;
	struct timeval	start;

	count = -1;
	if (init_mutex(philos, args->num_of_philo))
		return (printf("%s\n", ERR_MUTEX_INIT), 1);
	while (++count < args->num_of_philo)
		create_philo(&philos[count], count, philosophers);
	count = -1;
	philosophers->time.timestamp_ms = 0;
	gettimeofday(&start, 0);
	philosophers->time.start = start;
	while (++count < args->num_of_philo)
	{
		if (philos[count].philo_num == -1 || pthread_create(&philos[count].\
			thread, NULL, &routine, (void *)&philos[count]) || pthread_create(
				&philos[count].time_monitor, NULL, &time_routine,
				(void *)&philos[count]))
			return (printf("%s\n", ERR_PTHREAD), free(philos), free(args), 1);
	}
	return (0);
}

int	survival_conditions(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_thread_id >= 0)
		return (pthread_mutex_unlock(&philo->data->death_mutex), 3);
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data_mutex);
	if (philo->data->args->num_to_eat > 0
		&& philo->meal_counter >= philo->data->args->num_to_eat)
		return (pthread_mutex_unlock(&philo->data_mutex), 1);
	pthread_mutex_unlock(&philo->data_mutex);
	pthread_mutex_lock(&philo->data->time.time_mutex);
	get_timestamp(philo);
	if ((philo->data->time.timestamp_ms - philo->last_meal
			>= (philo->data->args->time_to_die / 1000)))
		return (pthread_mutex_unlock(&philo->data->time.time_mutex), 2);
	return (pthread_mutex_unlock(&philo->data->time.time_mutex), 0);
}
