/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:38:08 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/06 16:44:40 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>

# define ERR_USAGE "Usage: ./philo [Number of Philosophers] [Time to die]\
 [Time to eat] [Time to sleep] optional:[Number of times each Philosopher\
 must eat]"
# define ERR_MUTEX_INIT "Mutex Initialization failed"
# define ERR_TIME "gettimeofday() failed"
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
	long long		start;
	int				stop_printing;
	pthread_mutex_t	time_mutex;
	u_int64_t		timestamp_ms;
}	t_time;

typedef struct s_philo	t_philo;

typedef struct s_philos_data
{
	int				dead_thread_id;
	t_philo			*philos;
	t_args			*args;
	t_time			time;
	int				they_ate;
	pthread_mutex_t	death_mutex;
}	t_philos_data;

struct s_philo
{
	int				philo_num;
	int				fork_flag;
	u_int64_t		meal_counter;
	u_int64_t		last_meal;
	pthread_t		thread;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	fork_mutex;
	t_philos_data	*data;
};

//Same as standard atoi, except some minor changes to parsing
//characters specifically tailored to this program.
t_int			ft_atoi(const char *str);

//Initializes mutex's within all philos
int				init_mutex(t_philo *philos, int num_of_philo);

//Thread routine
void			*routine(void *var);

//Checks survival conditions and sets death accordingly
int				wellness_check(t_philo	*philo);

//Checks for death and prints message status if philo died
void			check_death(t_philo *philo);

//Sets up each philosopher with its respective values and pointers needed to
//function
void			create_philo(t_philo *philos, int num,
					t_philos_data *philosophers);

//Sets up the programs arguments needed for the threads
t_args			*set_args(int argc, char **argv);

//waits for all threads to die and destroys their mutex's
int				destroy_threads(t_philo *philos, int num_of_philo);

//Begins the process of creating pthreads
int				start_pthreads(t_philo *philos, t_args *args,
					t_philos_data *philosophers);

//Manages forks for a philosopher attempting to eat
int				philo_eat(t_philo *philo);

//Sleeps for time_to_sleep amount of time
int				philo_sleep(t_philo *philo);

//Prints out thinking philo state
int				philo_think(t_philo *philo);

//Sets the given philo timestamp to the current time
long long		get_timestamp(void);

//Checks the conditions needed by a philo to survive and eat again, or die
int				survival_conditions(t_philo *philo);

//Checks if all philos satisfy the num of times to eat including a
//self check on meal counter
int				check_thread_survival(t_philo *philo);

//Checks if all philosophers have satified the number of times to eat value
int				check_thread_continue(t_philo *philo);

//Unlocks forks for given philo and philo[next]
void			unlock_forks(t_philo *philo, int next);

//Checks if fork within given philo is free and reserves it
int				check_forks(t_philo *og_philo, t_philo *philo, int reserved);

//Sets up memory alloc and default values for t_philo_data
int				set_philo_data(t_philos_data *philosophers, t_args *args,
					t_philo *philos);

//Prints status messages based on given philo and given message
//is_eating value sets the timestamp of the status to the last_meal value
int				print_status(t_philo *philo, char *msg, int is_eating);

//Custom usleep for better accuracy and no delays
int				ft_usleep(t_philo *philo, uint64_t sleep_time);
#endif
