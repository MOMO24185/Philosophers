/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:38:08 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/20 14:52:23 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>

# define POOPOO_USAGE "Usage: ./philo [Number of Philosophers] [Time to die] [Time to eat] [Time to sleep] optional:[Number of times each Philosopher must eat]"

typedef struct s_args
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_to_eat;
}	t_args;

typedef struct s_int
{
	int	value;
	int	validity;
}	t_int;

typedef struct s_time
{
	struct timeval	timestamp;
	struct timeval	start;
	struct timeval	end;
	unsigned long	timestamp_ms;
	unsigned long	time_in_ms;
}	t_time;

typedef struct s_philo t_philo;

typedef struct s_philos_data
{
	int				dead_thread_id;
	t_philo			*philos;
	t_args			*args;
	pthread_mutex_t	philo_mutex;
}	t_philos_data;

struct s_philo
{
	int				philo_num;
	t_time			time;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	t_philos_data	*data;
};


t_int	ft_atoi(const char *str);

#endif
