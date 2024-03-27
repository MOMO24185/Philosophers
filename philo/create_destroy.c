/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:05 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/27 11:34:30 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	destroy_threads(t_philo *philos, int num_of_philo)
{
	int	count;

	count = 0;
	while (count < num_of_philo)
	{
		if (pthread_join(philos[count].thread, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&philos[count].fork_mutex, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&philos[count].data_mutex, NULL) != 0)
			return (1);
		count++;
	}
	return (0);
}

int	init_mutex(t_philo *philos, int num_of_philo)
{
	int	count;

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
	args->num_of_philo = ft_atoi(argv[1]).value;
	args->time_to_die = ft_atoi(argv[2]).value;
	args->time_to_eat = ft_atoi(argv[3]).value;
	args->time_to_sleep = ft_atoi(argv[4]).value;
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

t_philo	create_philo(int num, struct timeval start, t_philos_data *philosophers)
{
	t_philo	philo;

	philo.philo_num = num;
	philo.time.start = start;
	philo.data = philosophers;
	return (philo);
}
