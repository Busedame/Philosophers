/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:26:07 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 17:43:58 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Creds to Oceano for teaching me about getters and setters!! It is a super
good way to create more general functions that will be applicable to 
a wide range of actions.*/

/*Safely gets the current value of a bool.
@param mutex The mutex protecting the bool.
@param status A pointer to the current value of a bool.*/
bool	get_bool(pthread_mutex_t *mutex, bool *status)
{
	mutex_action(mutex, LOCK);
	if (*status)
	{
		mutex_action(mutex, UNLOCK);
		return (true);
	}
	else
	{
		mutex_action(mutex, UNLOCK);
		return (false);
	}
}

/*Safely updates the value of a bool.
@param mutex The mutex protecting the bool.
@param status A pointer to the current value of a bool.
@param new_status The new value of the bool.*/
void	set_bool(pthread_mutex_t *mutex, bool *status, bool new_status)
{
	mutex_action(mutex, LOCK);
	*status = new_status;
	mutex_action(mutex, UNLOCK);
}

/*Safely gets the current value of a long.
@param mutex The mutex protecting the long.
@param value The value of the long.
@param ret_value Stores the value of the long. A separate variable to be
able to safely return it without leaving the mutex unlocked.*/
long	get_long(pthread_mutex_t *mutex, long value)
{
	long	ret_value;

	mutex_action(mutex, LOCK);
	ret_value = value;
	mutex_action(mutex, UNLOCK);
	return (ret_value);
}

/*Safely updates the value of a long.
@param mutex The mutex protecting the long.
@param value A pointer to the current value of a long.
@param new_value The new value of the long.*/
void	set_long(pthread_mutex_t *mutex, long *value, long new_value)
{
	mutex_action(mutex, LOCK);
	*value = new_value;
	mutex_action(mutex, UNLOCK);
}

/*Safely increments the value of a long by 1.
@param mutex The mutex protecting the long.
@param value A pointer to the current value of a long.*/
void	add_one_to_long(pthread_mutex_t *mutex, long *value)
{
	mutex_action(mutex, LOCK);
	(*value)++;
	mutex_action(mutex, UNLOCK);
}
