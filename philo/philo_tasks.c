/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:50:53 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/07 15:52:09 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	eat(t_philo *philo, int first, int second)
{
	if (pthread_mutex_lock(&philo->data->forks[first]))
		return (0);
	if (!print_status(philo, "\033[1;36mHAS TAKEN A FORK\033[0m", 0))
		return (pthread_mutex_unlock(&philo->data->forks[first]), 0);
	if (pthread_mutex_lock(&philo->data->forks[second]))
		return (pthread_mutex_unlock(&philo->data->forks[first]), 0);
	if (!print_status(philo, "\033[1;36mHAS TAKEN A FORK\033[0m", 0))
		return (pthread_mutex_unlock(&philo->data->forks[first]),
		pthread_mutex_unlock(&philo->data->forks[second]), 0);
	if (!print_status(philo, "\033[1;32mIS EATING\033[0m", 1))
		return (pthread_mutex_unlock(&philo->data->forks[first]),
		pthread_mutex_unlock(&philo->data->forks[second]), 0);
	if (!ft_usleep(philo->data->args->time_to_eat))
		return (pthread_mutex_unlock(&philo->data->forks[first]),
		pthread_mutex_unlock(&philo->data->forks[second]), 0);
	pthread_mutex_lock(&philo->data->eater);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->data->eater);
	pthread_mutex_unlock(&philo->data->forks[first]);
	pthread_mutex_unlock(&philo->data->forks[second]);
	return (philo_sleep(philo));
}

int	philo_eat(t_philo *philo)
{
	int	first;
	int second;

	first = philo->philo_num;
	second = philo->philo_num + 1;
	if (second == philo->data->args->num_of_philo)
		second = 0;
	if (philo->data->args->num_of_philo == 1)
		second = -1;
	if (second != -1 && first > second)
		return (eat(philo, second, first));
	else if (second != -1)
		return (eat(philo, first, second));
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (!print_status(philo, "\033[1;33mIS SLEEPING\033[0m", 0))
		return (0);
	if (!ft_usleep(philo->data->args->time_to_sleep))
		return (0);
	return (1);
}

int	philo_think(t_philo *philo)
{
	if (!print_status(philo, "\033[1;37mIS THINKING\033[0m", 0))
		return (0);
	return (1);
}

int	print_status(t_philo *philo, char *msg, int is_eating)
{
	long long	time;

	time = get_timestamp() - philo->data->time.start;
	pthread_mutex_lock(&philo->data->printer);
	if (!philo->data->time.stop_printing && check_thread_continue(philo))
	{
		printf("TIMESTAMP[\033[1;37m%llu\033[0m]ms", time);
		printf(" THREAD[\033[1;37m%d\033[0m] ", philo->philo_num);
		printf("%s\n\033[0m", msg);
		if (is_eating == -1)
			philo->data->time.stop_printing = 1;
		pthread_mutex_unlock(&philo->data->printer);
		pthread_mutex_lock(&philo->data->eater);
		if (is_eating == 1)
			philo->last_meal = time;
		pthread_mutex_unlock(&philo->data->eater);
	}
	else
		return (pthread_mutex_unlock(&philo->data->printer), 0);
	return (1);
}
