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

typedef struct s_int
{
	int	value;
	int	validity;
}	t_int;

typedef struct s_time
{
	struct timeval	start;
	struct timeval	end;
	unsigned long	time_in_ms;
}	t_time;

typedef struct s_philo
{
	int				philo_num;
	t_time			time;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
}	t_philo;

t_int	ft_atoi(const char *str);

#endif
