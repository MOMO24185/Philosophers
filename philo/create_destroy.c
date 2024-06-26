/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:05 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/18 12:55:01 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	set_philo_data(t_philos_data *philosophers, t_args *args, t_philo *philos)
{
	philosophers->dead_thread_id = -1;
	philosophers->they_ate = 0;
	philosophers->time.stop_printing = 0;
	philosophers->args = args;
	philosophers->philos = philos;
	if (pthread_mutex_init(&philosophers->time.time_mutex, NULL) != 0)
		return (free(philosophers), free(args), free(philos), 1);
	if (pthread_mutex_init(&philosophers->death_mutex, NULL) != 0)
		return (free(philosophers), free(args), free(philos), 1);
	return (0);
}

int	destroy_threads(t_philo *philos, int num_of_philo)
{
	int	count;

	count = 0;
	while (count < num_of_philo)
	{
		if (pthread_join(philos[count].thread, NULL) != 0)
			return (1);
		if (pthread_join(philos[count].time_monitor, NULL) != 0)
			return (1);
		if (pthread_mutex_destroy(&philos[count].fork_mutex) != 0)
			return (1);
		if (pthread_mutex_destroy(&philos[count].data_mutex) != 0)
			return (1);
		count++;
	}
	if (pthread_mutex_destroy(&philos[--count].data->time.time_mutex) != 0)
		return (1);
	return (0);
}

int	init_mutex(t_philo *philos, int num_of_philo)
{
	int				count;

	count = 0;
	while (count < num_of_philo)
	{
		if (pthread_mutex_init(&philos[count].fork_mutex, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&philos[count].data_mutex, NULL) != 0)
			return (1);
		count++;
	}
	return (0);
}

t_args	*set_args(int argc, char **argv)
{
	t_args	*args;
	int		count;

	count = 0;
	args = malloc(sizeof(t_args));
	if (!args)
		return (args);
	args->num_of_philo = ft_atoi(argv[1]).value;
	args->time_to_die = ft_atoi(argv[2]).value * 1000;
	args->time_to_eat = ft_atoi(argv[3]).value * 1000;
	args->time_to_sleep = ft_atoi(argv[4]).value * 1000;
	if (argc == 6)
		args->num_to_eat = ft_atoi(argv[5]).value;
	else
		args->num_to_eat = 0;
	while (++count < argc)
	{
		if (ft_atoi(argv[count]).validity == -1)
			args->num_of_philo = -1;
	}
	return (args);
}

void	create_philo(t_philo *philos, int num, t_philos_data *philosophers)
{
	philos->philo_num = num;
	philos->data = philosophers;
	philos->fork_flag = -1;
	philos->meal_counter = 0;
	philos->last_meal = 0;
}
