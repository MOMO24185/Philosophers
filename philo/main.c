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

unsigned long	get_time_in_ms(t_time time)
{
	return ((time.end.tv_sec * 1000000) + time.end.tv_usec) - ((time.start.tv_sec * 1000000) + time.start.tv_usec);
}

void	*say_something(void *var)
{
	t_philo	*philo;

	philo = var;
	pthread_mutex_lock(&philo->fork_mutex);
	gettimeofday(&philo->time.end, 0);
	philo->time.time_in_ms = get_time_in_ms(philo->time);
	printf("%ldms	Thread %d is saying something\n", philo->time.time_in_ms, philo->philo_num); 
	pthread_mutex_unlock(&philo->fork_mutex);
	return (NULL);
}

t_philo	create_philo(int num, struct timeval	start)
{
	t_philo	philo;

	philo.philo_num = num;
	philo.time.start = start;
	pthread_mutex_init(&philo.fork_mutex, NULL);
	return (philo);
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
	t_philo			*philosophers;
	t_int			num_of_philo;
	void			*var;
	int				count;
	struct timeval	start;

	if (argc > 6 || argc < 5)
		return (printf("%s\n", POOPOO_USAGE), 1);
	num_of_philo = ft_atoi(argv[1]);
	if (num_of_philo.validity == -1)
		exit (EXIT_FAILURE);
	philosophers = malloc(num_of_philo.value * sizeof(t_philo));
	count = 0;
	gettimeofday(&start, 0);
	while (count < num_of_philo.value)
	{
		philosophers[count] = create_philo(count, start);
		var = &philosophers[count];
		if (philosophers[count].philo_num == -1)
			return (free(philosophers), 1);
		if (pthread_create(&philosophers[count].thread, NULL, &say_something, var) != 0)
			philosophers[count].philo_num = -1;
		printf("Philo (%d) created\n", philosophers[count].philo_num);
		count++;
	}
	count = 0;
	while (count < num_of_philo.value)
	{
		pthread_join(philosophers[count].thread, NULL);
		while (pthread_mutex_destroy(&philosophers[count].fork_mutex) != 0)
			;
		count++;
	}
	return (free(philosophers), 0);
}
