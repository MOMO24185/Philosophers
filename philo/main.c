/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:39:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/14 14:28:08 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*say_something(t_philo philo)
{
	printf("Thread number %u is saying something\n", philo.philo_num);
	return (NULL);
}

t_philo	create_philo(int num)
{
	t_philo	philo;

	philo.philo_num = num;
	if (pthread_create(&philo.thread, NULL, say_something(philo), NULL) != 0)
		exit (num);
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philosophers;
	int		count;
	t_int	num_of_philo;

	if (argc > 6 || argc < 5)
		return (printf("Wrong number of arguments\n"), 1);
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
		printf("")
		count++;
	}
	count = 0;
	while (count >= 0)
	{
		printf("THREAD JOIN (%d)", pthread_join(philosophers[count].thread, NULL));
		count++;
	}
	return (0);
}
