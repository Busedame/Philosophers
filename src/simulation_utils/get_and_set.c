/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:26:07 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/20 12:03:07 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	set_bool(pthread_mutex_t *mutex, bool *status, bool new_status)
{
	mutex_action(mutex, LOCK);
	*status = new_status;
	mutex_action(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long value)
{
	long	ret_value;

	mutex_action(mutex, LOCK);
	ret_value = value;
	mutex_action(mutex, UNLOCK);
	return (ret_value);
}

void	set_long(pthread_mutex_t *mutex, long *value, long new_value)
{
	mutex_action(mutex, LOCK);
	*value = new_value;
	mutex_action(mutex, UNLOCK);
}

void	add_one_to_long(pthread_mutex_t *mutex, long *value)
{
	mutex_action(mutex, LOCK);
	(*value)++;
	mutex_action(mutex, UNLOCK);
}
