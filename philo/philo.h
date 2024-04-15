/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:38:08 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/15 19:00:12 by melshafi         ###   ########.fr       */
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

# define ERR_USAGE "Usage: ./philo [Number of Philosophers] [Time to die]\
 [Time to eat] [Time to sleep] optional:[Number of times each Philosopher\
 must eat]"
# define ERR_MUTEX_INIT "Mutex Initialization failed"
# define ERR_ARGS "Invalid Arguments"
# define ERR_THREAD_DESTROY "Threads/Mutex's failed to stop"
# define ERR_PTHREAD "A PTHREAD failed to start"

typedef struct s_args
{
	int				num_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_to_eat;
}	t_args;

typedef struct s_int
{
	int	value;
	int	validity;
}	t_int;

typedef struct s_time
{
	struct timeval	start;
	struct timeval	end;
	u_int64_t		timestamp_ms;
}	t_time;

typedef struct s_philo	t_philo;

typedef struct s_philos_data
{
	int				dead_thread_id;
	t_philo			*philos;
	t_args			*args;
	t_time			time;
	pthread_t		death_thread;
	pthread_mutex_t	death_mutex;
}	t_philos_data;

struct s_philo
{
	int				philo_num;
	int				thread_continue;
	int				fork_flag;
	u_int64_t		meal_counter;
	u_int64_t		last_meal;
	pthread_t		thread;
	pthread_t		time_monitor;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	time_mutex;
	t_philos_data	*data;
};

//Same as standard atoi, except some minor changes to parsing forbidden
//characters specifically tailored to this program.
t_int			ft_atoi(const char *str);

//Initializes mutex's within all philos
int				init_mutex(t_philo *philos, int num_of_philo);

//Calculates time between 2 intervals in milliseconds
unsigned long	get_time_in_ms(struct timeval start, struct timeval end);

//Thread routine
void			*routine(void *var);

//Sets up each philosopher with its respective values and pointers needed to
//function
void			create_philo(t_philo *philos, int num, t_philos_data \
					*philosophers);

//Sets up the programs arguments needed for the threads
t_args			*set_args(int argc, char **argv);

//Ends all threads and destroys their mutex's
int				destroy_threads(t_philo *philos, int num_of_philo);

//Begins the process of creating pthreads
int				start_pthreads(t_philo *philos, t_args *args, t_philos_data \
					*philosophers);

//Manages forks for a philosopher attempting to eat
int				philo_eat(t_philo *philo);

//Sleeps for time_to_sleep amount of time
void			philo_sleep(t_philo *philo);

//Only prints current philo state as thinking
void			philo_think(t_philo *philo);

//Sets the given philo timestamp to the current time
void			get_timestamp(t_philo *philo);

//Sets the given philo last_meal timestamp to the current time
void			get_last_meal_time(t_philo *philo);

//Custom usleep that is more accurate and precise
void			nap(u_int64_t utime, t_philo philo);

//Checks the conditions needed by a philo to survive and eat again, or die
int				survival_conditions(t_philo *philo);
#endif
