/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:00:32 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 16:05:14 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Creates, runs and joins all the philosopher threads + the monitor thread.
Returns 1 if something went wrong with thread creation/joining or memory
allocation.
Returns 0 upon success.*/
int	simulation(t_main *main, t_args *args)
{
	t_monitor	*monitor;
	int			i;

	i = 0;
	monitor = NULL;
	while (i < args->tot_phil)
	{
		if (pthread_create(main->philo[i]->philo, NULL, &philo_routine, \
		main->philo[i]) != 0)
			return (1);
		i++;
	}
	monitor = init_and_start_monitor(main, monitor);
	if (!monitor)
		return (free_monitor(monitor, true));
	i = 0;
	while (i < args->tot_phil)
	{
		if (pthread_join(*main->philo[i]->philo, NULL) != 0)
			return (2);
		i++;
	}
	free_monitor(monitor, false);
	return (0);
}
