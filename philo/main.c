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

void	*say_something()
{
	printf("Thread is saying something\n");
	return (NULL);
}

t_philo	create_philo(int num)
{
	t_philo	philo;

	philo.philo_num = num;
	if (pthread_create(&philo.thread, NULL, &say_something, NULL) != 0)
		philo.philo_num = -1;
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philosophers;
	t_int	num_of_philo;
	t_time	time;
	int		count;

	if (argc > 6 || argc < 5)
		return (printf("Wrong number of arguments\n"), 1);
	gettimeofday(&time.start, 0);
	printf("Number of Philosophers (%s)\n", argv[1]);
	printf("Time to die (%s)\n", argv[2]);
	printf("Time to eat (%s)\n", argv[3]);
	printf("Time to sleep (%s)\n", argv[4]);
	if (argc == 6)
		printf("Number of times each Philosopher must eat (%s)\n", argv[5]);
	num_of_philo = ft_atoi(argv[1]);
	if (num_of_philo.validity == -1)
		exit (EXIT_FAILURE);
	philosophers = malloc(num_of_philo.value * sizeof(t_philo));
	count = 0;
	while (count < num_of_philo.value)
	{
		philosophers[count] = create_philo(count);
		if (philosophers[count].philo_num == -1)
			return (free(philosophers), 1);
		gettimeofday(&time.end, 0);
		time.time_in_ms = ((time.end.tv_sec * 1000000) + time.end.tv_usec) - ((time.start.tv_sec * 1000000) + time.start.tv_usec);
		printf("Philo (%d) Time (%ld)\n", philosophers[count].philo_num, time.time_in_ms);
		count++;
	}
	count = 0;
	while (count < num_of_philo.value)
	{
		printf("THREAD JOIN (%d)\n", pthread_join(philosophers[count].thread, NULL));
		count++;
	}
	return (free(philosophers), 0);
}
