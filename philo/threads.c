/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/06 14:46:08 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	check_death(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead_thread_id == -1)
	{
		philo->data->dead_thread_id = philo->philo_num;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->time.time_mutex);
		philo->data->time.stop_printing = 1;
		pthread_mutex_unlock(&philo->data->time.time_mutex);
		time = get_timestamp() - philo->data->time.start;
		printf("TIMESTAMP[\033[1;37m%llu\033[0m]ms ", time);
		printf("THREAD[\033[1;37m%d\033[0m] ", philo->philo_num);
		printf("\033[1;31mIS DEAD\n\033[0m");
	}
	else
		pthread_mutex_unlock(&philo->data->death_mutex);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	if (philo->philo_num % 2 == 1)
		ft_usleep(philo, philo->data->args->time_to_eat);
	while (check_thread_continue(philo))
	{
		if (philo_eat(philo))
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

	count = -1;
	if (init_mutex(philos, args->num_of_philo))
		return (printf("%s\n", ERR_MUTEX_INIT), 1);
	while (++count < args->num_of_philo)
		create_philo(&philos[count], count, philosophers);
	count = -1;
	philosophers->time.start = get_timestamp();
	while (++count < args->num_of_philo)
	{
		if (philos[count].philo_num == -1 || pthread_create(&philos[count].\
			thread, NULL, &routine, (void *)&philos[count]))
			return (printf("%s\n", ERR_PTHREAD), free(philos), free(args), 1);
	}
	return (0);
}

int	wellness_check(t_philo	*philo)
{
	int		value;

	value = survival_conditions(philo);
	if (value == 0)
		return (0);
	else if (value == 1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->they_ate++;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	else if (value == 2)
		return (check_death(philo), 2);
	else if (value == 3)
		return (3);
	return (0);
}

int	survival_conditions(t_philo *philo)
{
	long long	time;

	time = get_timestamp() - philo->data->time.start;
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
	if ((time - philo->last_meal
			>= (philo->data->args->time_to_die / 1000)))
		return (pthread_mutex_unlock(&philo->data->time.time_mutex), 2);
	return (pthread_mutex_unlock(&philo->data->time.time_mutex), 0);
}
