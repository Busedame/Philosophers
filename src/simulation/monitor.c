/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:30:49 by nholbroo          #+#    #+#             */
/*   Updated: 2024/10/01 13:27:19 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Iterates through all the philosophers, checking if ALL are full, by
accessing their separate bools "full".
Returns 1 if one of them isn't full, meaning all philos are NOT full. 
Returns 0 if all philos are full, and sets the bool all_philos_full to true.*/
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

/*The monitor routine works in an infinite loop.
It will only stop if:
-> All philosophers have eaten all their meals (as specified by the optional
argument).
-> If a philosopher dies.
In the case of all philosophers being full, the monitor thread will exit the
loop. The philosopher threads will exit too, after having finished their
routines.
In the case of a philosopher dying, it will set the bool "someone_died" to
true, notifying all the philosophers that someone died. In that case, all
threads will end, and the simulation/program stops.*/
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
			do_action(500);
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

/*Allocates memory for the monitor thread, and starts + ends the monitor
thread if there is more than one philosopher. If there is only one, it
is not really needed, as the philo will die anyway.*/
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
	if (main->philo[0]->args->tot_phil != 1)
	{
		pthread_create(monitor->monitor, NULL, &monitor_routine, monitor);
		pthread_join(*monitor->monitor, NULL);
	}
	return (monitor);
}
