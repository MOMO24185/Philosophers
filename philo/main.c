/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:39:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/17 16:12:03 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

/*
Debug in valgrind using these flags for tracking threads and mutex states
valgrind --tool=helgrind --history-level=full --track-lockorders=yes
--free-is-write=yes
*/

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
	if (args->num_of_philo <= -1 || args->num_of_philo > 200
		|| args->time_to_die < 60000 || args->time_to_eat < 60000
		|| args->time_to_sleep < 60000)
		return (free(args), printf("%s\n", ERR_ARGS), 1);
	if (args->num_of_philo == 1)
		return (0);
	philos = malloc(args->num_of_philo * sizeof(t_philo));
	philosophers = malloc(sizeof(t_philos_data));
	philosophers->args = args;
	philosophers->dead_thread_id = -1;
	philosophers->they_ate = 0;
	if (pthread_mutex_init(&philosophers->time.time_mutex, NULL) != 0)
		return (free(philos), free(args), 1);
	if (pthread_mutex_init(&philosophers->death_mutex, NULL) != 0)
		return (free(philos), free(args), 1);
	philosophers->philos = philos;
	if (start_pthreads(philos, args, philosophers) != 0)
		return (1);
	if (destroy_threads(philos, args->num_of_philo))
		return (printf("%s\n", ERR_THREAD_DESTROY), 1);
	return (free(philos), free(args), free(philosophers), 0);
}
