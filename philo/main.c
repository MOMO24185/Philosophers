/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:39:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/20 14:45:41 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// Debug in valgrind using these flags for tracking threads and mutex states
// valgrind --tool=helgrind --history-level=full --track-lockorders=yes --free-is-write=yes

unsigned long	get_time_in_ms(struct timeval start, struct timeval end)
{
	return ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);
}

void	*say_something(void *var)
{
	t_philo	*philo;

	philo = var;
	pthread_mutex_lock(&philo->fork_mutex);
	gettimeofday(&philo->time.start, 0);
	gettimeofday(&philo->time.end, 0);
	philo->time.time_in_ms = get_time_in_ms(philo->time.start, philo->time.end);
	philo->time.timestamp_ms = get_time_in_ms(philo->time.timestamp, philo->time.end);
	printf("Timestamp: %ldms Philosopher %d is saying something in %ldms\n", philo->time.timestamp_ms, philo->philo_num, philo->time.time_in_ms); 
	pthread_mutex_unlock(&philo->fork_mutex);
	return (NULL);
}

t_philo	create_philo(int num, struct timeval start, t_philos_data *philosophers)
{
	t_philo	philo;

	philo.philo_num = num;
	philo.time.timestamp = start;
	philo.data = philosophers;
	return (philo);
}

t_args	*set_args(int argc, char **argv)
{
	t_args *args;
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

/*
Takes in these arguments:
[Number of Philosophers]
[Time to die]
[Time to eat]
[Time to sleep]

Optional:
[Number of times each Philosopher must eat]
*/
int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_args			*args;
	int				count;
	struct timeval	start;
	t_philos_data philosophers;

	if (argc > 6 || argc < 5)
		return (printf("%s\n", POOPOO_USAGE), 1);
	args = set_args(argc, argv);
	if (args->num_of_philo == -1)
		exit (EXIT_FAILURE);
	philos = malloc(args->num_of_philo * sizeof(t_philo));
	philosophers.args = args;
	count = 0;
	while (count < args->num_of_philo)
		pthread_mutex_init(&philos[count++].fork_mutex, NULL);
	pthread_mutex_init(&philosophers.philo_mutex, NULL);
	count = 0;
	gettimeofday(&start, 0);
	philosophers.philos = philos;
	while (count < args->num_of_philo)
	{
		philos[count] = create_philo(count, start, &philosophers);
		if (philos[count].philo_num == -1)
			return (free(philos), 1);
		if (pthread_create(&philos[count].thread, NULL, &say_something, (void *)&philos[count]) != 0)
			philos[count].philo_num = -1;
		printf("Thread (%d) created\n", philos[count].philo_num);
		count++;
	}
	count = 0;
	while (count < args->num_of_philo)
	{
		pthread_join(philos[count].thread, NULL);
		while (pthread_mutex_destroy(&philos[count].fork_mutex) != 0)
			;
		count++;
	}
	pthread_mutex_destroy(&philosophers.philo_mutex);
	return (free(philos), free(args), 0);
}
