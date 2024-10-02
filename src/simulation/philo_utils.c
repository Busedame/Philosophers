/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:01:58 by nholbroo          #+#    #+#             */
/*   Updated: 2024/10/02 15:45:41 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*First gets the start time. Then starts a while loop taking the start time - 
the current time, as long as it is less than the total duration. Any time
this is true, it sleeps for total duration divided by 100, in order to keep
round numbers. A calculation to get the time stamps correct, because the
usleep function is a bit inaccurate. Also uses a duration that is calculated
in relation to sleep, eat and die time.*/
void	super_duper_usleep(long duration)
{
	long	timestamp;

	timestamp = get_current_time();
	while (get_current_time() - timestamp < duration)
		usleep(duration);
}

/*Checks if any philosopher died. The someone_died bool is set by the
monitor thread.*/
int	philo_is_dead(t_philo *philo)
{
	if (get_bool(&philo->mutex->status, &philo->args->someone_died))
		return (1);
	return (0);
}

/*Checks if the current philosopher has eaten all their meals. */
int	is_philo_full(t_philo *philo)
{
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], LOCK);
	if (philo->args->opt_arg && philo->meals_eaten == philo->args->max_eat)
	{
		philo->full = true;
		mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
		return (1);
	}
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
	return (0);
}
