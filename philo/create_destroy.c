/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:13:05 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/14 16:30:33 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	set_philo_data(t_philos_data *philosophers, t_args *args, t_philo *philos)
{
	philosophers->dead_thread_id = -1;
	philosophers->they_ate = 0;
	philosophers->args = args;
	philosophers->philos = philos;
	return (0);
}

int	destroy_threads(t_philos_data *philosophers, int num_of_philo)
{
	int	count;

	count = 0;
	while (++count <= num_of_philo)
	{
		if (pthread_join(philosophers->philos[count].thread, NULL))
			return (1);
	}
	count = 0;
	while (++count <= num_of_philo)
	{
		if (pthread_mutex_destroy(&philosophers->forks[count]))
			return (1);
	}
	if (pthread_mutex_destroy(&philosophers->printer))
		return (1);
	if (pthread_mutex_destroy(&philosophers->eater))
		return (1);
	if (pthread_mutex_destroy(&philosophers->death))
		return (1);
	free(philosophers->forks);
	return (0);
}

int	init_mutex(t_philos_data *philosophers, int num_of_philo)
{
	int				count;

	count = 1;
	philosophers->forks = malloc(sizeof(pthread_mutex_t) * (num_of_philo + 1));
	while (count <= num_of_philo)
	{
		if (pthread_mutex_init(&philosophers->forks[count], NULL) != 0)
			return (printf("MUTEX_INIT FATAL ERROR\n"), 1);
		count++;
	}
	if (pthread_mutex_init(&philosophers->eater, NULL) != 0)
		return (printf("MUTEX_INIT FATAL ERROR\n"), 1);
	if (pthread_mutex_init(&philosophers->printer, NULL) != 0)
		return (printf("MUTEX_INIT FATAL ERROR\n"), 1);
	if (pthread_mutex_init(&philosophers->death, NULL) != 0)
		return (printf("MUTEX_INIT FATAL ERROR\n"), 1);
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

void	create_philo(t_philo *philos, int num, t_philos_data *philosophers)
{
	philos->philo_num = num;
	philos->data = philosophers;
	philos->meal_counter = 0;
	philos->last_meal = 0;
	philos->fork_taken = 0;
	philos->is_eating = 0;
}
