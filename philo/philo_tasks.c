/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:50:53 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/14 16:25:27 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	eat(t_philo *philo, int left, int right)
{
	lock_forks(philo, left, right);
	if (!print_status(philo, "\033[1;32mIS EATING\033[0m", 1))
		return (pthread_mutex_unlock(&philo->data->forks[left]),
			pthread_mutex_unlock(&philo->data->forks[right]), 0);
	pthread_mutex_lock(&philo->data->eater);
	philo->meal_counter++;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->data->eater);
	if (!ft_usleep(philo, philo->data->args->time_to_eat))
		return (pthread_mutex_unlock(&philo->data->forks[left]),
			pthread_mutex_unlock(&philo->data->forks[right]), 0);
	philo->data->philos[left].fork_taken = 0;
	philo->data->philos[right].fork_taken = 0;
	pthread_mutex_lock(&philo->data->eater);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->eater);
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_unlock(&philo->data->forks[right]);
	return (philo_sleep(philo));
}

int	philo_eat(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->philo_num;
	right = philo->philo_num + 1;
	if (right == philo->data->args->num_of_philo + 1)
		right = 0;
	if (philo->data->args->num_of_philo == 1)
		right = -1;
	if (right != -1 && left > right)
		return (eat(philo, right, left));
	else if (right != -1)
		return (eat(philo, left, right));
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (!print_status(philo, "\033[1;33mIS SLEEPING\033[0m", 0))
		return (0);
	if (!ft_usleep(philo, philo->data->args->time_to_sleep))
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
	if (check_death_continue(philo) || is_eating == -1)
	{
		printf("TIMESTAMP[\033[1;37m%llu\033[0m]ms", time);
		printf(" THREAD[\033[1;37m%d\033[0m] ", philo->philo_num);
		printf("%s\n\033[0m", msg);
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
