/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:39:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/07 14:54:26 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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
	t_philos_data	*philosophers;

	if (argc > 6 || argc < 5)
		return (printf("%s\n", ERR_USAGE), 1);
	args = set_args(argc, argv);
	if (!args || args->num_of_philo == 0)
		return (1);
	if (args->num_of_philo < 0 || args->num_of_philo > 200
		|| args->time_to_die < 60000 || args->time_to_eat < 60000
		|| args->time_to_sleep < 60000)
		return (free(args), printf("%s\n", ERR_ARGS), 1);
	philos = malloc(args->num_of_philo * sizeof(t_philo));
	philosophers = malloc(sizeof(t_philos_data));
	if (!philosophers || !philos)
		return (free(args), free(philos), 1);
	if (set_philo_data(philosophers, args, philos))
		return (1);
	if (start_pthreads(philos, args, philosophers))
		return (1);
	if (destroy_threads(philosophers, args->num_of_philo))
		return (printf("%s\n", ERR_THREAD_DESTROY), 1);
	return (free(philos), free(args), free(philosophers), 0);
}
