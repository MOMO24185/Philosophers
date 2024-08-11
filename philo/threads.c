/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:12:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/07 15:36:35 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	check_death(t_philos_data *philosophers)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < philosophers->args->num_of_philo)
		{
			if (wellness_check(&philosophers->philos[i]) == 2)
				return ;
		}
		pthread_mutex_lock(&philosophers->death);
		if (philosophers->dead_thread_id >= 0)
			return ((void)pthread_mutex_unlock(&philosophers->death));
		pthread_mutex_unlock(&philosophers->death);
	}
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = var;
	if (philo->philo_num % 2 == 1)
	{
		if (!ft_usleep(philo->data->args->time_to_eat))
			return ((void *)0);
	}
	while (!wellness_check(philo) && check_thread_continue(philo))
	{
		if (!philo_eat(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return ((void *)0);
}

int	start_pthreads(t_philo *philos, t_args *args, t_philos_data *philosophers)
{
	int				count;

	count = -1;
	if (init_mutex(philosophers, args->num_of_philo))
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
	return (check_death(philosophers), 0);
}

int	wellness_check(t_philo	*philo)
{
	int		value;

	value = survival_conditions(philo);
	if (value == 1)
	{
		pthread_mutex_lock(&philo->data->eater);
		philo->data->they_ate++;
		pthread_mutex_unlock(&philo->data->eater);
		return (1);
	}
	else if (value == 2)
	{
		pthread_mutex_lock(&philo->data->death);
		philo->data->dead_thread_id = philo->philo_num;
		pthread_mutex_unlock(&philo->data->death);
		print_status(philo, "\033[1;31mIS DEAD\033[0m", -1);
		return (2);
	}
	else if (value == 3)
		return (3);
	return (0);
}

int	survival_conditions(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&philo->data->death);
	if (philo->data->dead_thread_id >= 0)
		return (pthread_mutex_unlock(&philo->data->death), 3);
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_lock(&philo->data->eater);
	if (philo->data->args->num_to_eat > 0
		&& philo->meal_counter >= philo->data->args->num_to_eat)
		return (pthread_mutex_unlock(&philo->data->eater), 1);
	pthread_mutex_unlock(&philo->data->eater);
	time = get_timestamp() - philo->data->time.start;
	pthread_mutex_lock(&philo->data->eater);
	if ((time - philo->last_meal
			>= (philo->data->args->time_to_die / 1000)))
		return (pthread_mutex_unlock(&philo->data->eater), 2);
	pthread_mutex_unlock(&philo->data->eater);
	return (0);
}
