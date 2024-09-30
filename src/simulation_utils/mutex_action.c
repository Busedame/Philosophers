/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:44:38 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/19 14:45:24 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_action(pthread_mutex_t *mutex, int action)
{
	if (action == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (1);
	}
	else if (action == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (1);
	}
	else if (action == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (1);
	}
	else if (action == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (1);
	}
	return (0);
}
