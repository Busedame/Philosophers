/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:17:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/28 16:08:25 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_time(t_main *main)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (1);
	main->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

long	get_current_time(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	timestamp_for_meal(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (1);
	philo->last_eaten = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (0);
}

long	time_elapsed_since_last_meal(t_philo *philo)
{
	struct timeval	tv;
	long			current_time;
	long			elapsed_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	current_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	elapsed_time = current_time - philo->last_eaten;
	return (elapsed_time);
}

long	time_elapsed_since_start(t_philo *philo)
{
	struct timeval	tv;
	long			current_time;
	long			elapsed_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	current_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	elapsed_time = current_time - philo->start_time;
	return (elapsed_time);
}
