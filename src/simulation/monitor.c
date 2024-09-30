/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:30:49 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 14:24:38 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	are_all_philos_full(t_monitor *monitor)
{
	int	i;

	i = 0;
	while (i < monitor->main->philo[0]->args->tot_phil - 1)
	{
		if (!get_bool(&monitor->main->mutex->philo[i], \
		&monitor->main->philo[i]->full))
			return (1);
		i++;
	}
	set_bool(&monitor->main->mutex->status, \
	&monitor->main->philo[0]->args->all_philos_full, true);
	return (0);
}

void	*monitor_routine(void *ptr)
{
	int			i;
	t_monitor	*monitor;

	monitor = (t_monitor *)ptr;
	while (1)
	{
		i = 0;
		while (monitor->main->philo[i])
		{
			usleep(1000);
			if (!are_all_philos_full(monitor))
				return (NULL);
			if (time_elapsed_since_last_meal(monitor->main->philo[i]) >= \
				monitor->main->philo[i]->args->t_to_die && \
				are_all_philos_full(monitor))
			{
				set_bool(&monitor->main->mutex->status, \
				&monitor->main->philo[i]->args->someone_died, true);
				print_death(monitor->main->philo[i]);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

t_monitor	*init_and_start_monitor(t_main *main, t_monitor *monitor)
{
	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	monitor->main = main;
	monitor->monitor = malloc(sizeof(pthread_t));
	if (!monitor->monitor)
	{
		free(monitor);
		return (NULL);
	}
	pthread_create(monitor->monitor, NULL, &monitor_routine, monitor);
	pthread_join(*monitor->monitor, NULL);
	return (monitor);
}
