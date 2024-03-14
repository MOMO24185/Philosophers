/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:17:14 by melshafi          #+#    #+#             */
/*   Updated: 2024/03/14 10:35:21 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	overflow_check(int count, int status)
{
	if (count > 19)
		return (-1);
	return (status);
}

static int	forbidden_check(const char *str)
{
	int	count;

	count = 0;
	while (str[count])
	{
		if (str[count] < '0' || str[count] > '9')
			return (1);
		count++;
	}
	return (0);
}

t_int	ft_atoi(const char *str)
{
	t_int				returned;
	int					count;
	long long			result;
	int					minus_sign;

	count = 0;
	result = 0;
	minus_sign = 1;
	returned.validity = 1;
	if (forbidden_check(str) || str[count] == '-')
		returned.validity = -1;
	if (str[count] == '-' || str[count] == '+')
		count++;
	while (str[count] >= '0' && str[count] <= '9')
	{
		result *= 10;
		result += str[count++] - '0';
		returned.validity = overflow_check(count, returned.validity);
	}
	returned.value = result * minus_sign;
	if (result * minus_sign > INT_MAX || result * minus_sign < INT_MIN)
		returned.validity = -1;
	return (returned);
}
