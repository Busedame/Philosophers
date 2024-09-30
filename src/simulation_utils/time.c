/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:17:18 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 17:38:12 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*At the start of the program, set the main->start_time to the current time.
This is since the gettimeofday gets the time elapsed since 1970 or something,
and we don't care about that - we want the time elapsed since program start.*/
int	init_time(t_main *main)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (1);
	main->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (0);
}

/*Gets the current time in milliseconds.*/
long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*Sets the philo->last_eaten to the current time. This will get called
whenever a philosopher starts eating. It is protected by a mutex, because
the monitor thread will access this variable regularly.*/
int	timestamp_for_meal(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (1);
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], LOCK);
	philo->last_eaten = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
	return (0);
}

/*Checks how much time has elapsed since the last meal. Protected by a mutex
since there is shared data between the monitor thread and the current philo.*/
long	time_elapsed_since_last_meal(t_philo *philo)
{
	struct timeval	tv;
	long			current_time;
	long			elapsed_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	current_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], LOCK);
	elapsed_time = current_time - philo->last_eaten;
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
	return (elapsed_time);
}

/*Used for timestamps in the printing. How much time has passed since the
beginning of the program.*/
long	time_elapsed_since_start(t_philo *philo)
{
	struct timeval	tv;
	long			current_time;
	long			elapsed_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	current_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], LOCK);
	elapsed_time = current_time - philo->start_time;
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
	return (elapsed_time);
}
