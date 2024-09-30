/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:17:24 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 15:28:27 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Destroys the mutexes and the pointers to them.
The mutexes created are two arrays, and the rest are single mutexes.
The mutexes must be destroyed, and the pointers to them are getting freed.*/
static void	free_mutexes(t_main *main)
{
	int	i;

	if (main->mutex)
	{
		if (main->mutex->fork)
		{
			i = 0;
			while (i < main->philo[i]->args->tot_phil - 1)
				mutex_action(&main->mutex->fork[i++], DESTROY);
			free(main->mutex->fork);
		}
		if (main->mutex->philo)
		{
			i = 0;
			while (i < main->philo[i]->args->tot_phil - 1)
				mutex_action(&main->mutex->philo[i++], DESTROY);
			free(main->mutex->philo);
		}
		mutex_action(&main->mutex->eating, DESTROY);
		mutex_action(&main->mutex->print, DESTROY);
		mutex_action(&main->mutex->start, DESTROY);
		mutex_action(&main->mutex->status, DESTROY);
		free(main->mutex);
	}
}

/*Destroys and frees mutexes, and frees all allocated memory of the main
struct.*/
void	free_main_struct(t_main *main)
{
	int	i;

	if (main)
	{
		free_mutexes(main);
		if (main->philo)
		{
			i = 0;
			while (main->philo[i])
			{
				if (main->philo[i]->philo)
					free(main->philo[i]->philo);
				free(main->philo[i]);
				i++;
			}
			free(main->philo);
		}
	}
}

/*Frees all allocated memory of the monitor struct.*/
int	free_monitor(t_monitor *monitor, bool error)
{
	if (monitor)
	{
		if (monitor->monitor)
			free(monitor->monitor);
		free(monitor);
	}
	if (error)
		return (2);
	return (0);
}
