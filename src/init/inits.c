/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:13:01 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 14:57:04 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_main *main, t_args *args)
{
	int	i;

	i = 0;
	main->mutex = malloc(sizeof(t_mutex));
	if (!main->mutex)
		return (1);
	main->mutex->fork = malloc(sizeof(pthread_mutex_t) * (args->tot_phil + 1));
	if (!main->mutex->fork)
		return (1);
	main->mutex->philo = malloc(sizeof(pthread_mutex_t) * (args->tot_phil + 1));
	if (!main->mutex->fork)
		return (1);
	mutex_action(&main->mutex->print, INIT);
	mutex_action(&main->mutex->status, INIT);
	mutex_action(&main->mutex->eating, INIT);
	mutex_action(&main->mutex->start, INIT);
	while (i <= args->tot_phil)
	{
		mutex_action(&main->mutex->fork[i], INIT);
		mutex_action(&main->mutex->philo[i], INIT);
		i++;
	}
	return (0);
}

static int	first_init(t_main *main, t_args *args)
{
	main->philo = malloc(sizeof(t_philo *) * (args->tot_phil + 1));
	if (!main->philo)
		return (1);
	if (init_mutex(main, args))
		return (1);
	return (0);
}

static void	init_forks(t_main *main, t_args *args, int i)
{
	if (main->philo[i]->no_philo == 1)
		main->philo[i]->forks[1] = args->tot_phil;
	else
		main->philo[i]->forks[1] = main->philo[i]->no_philo - 1;
	main->philo[i]->forks[0] = main->philo[i]->no_philo;
}

static void	set_struct_members_to_zero(t_philo **philo)
{
	(*philo)->last_eaten = 0;
	(*philo)->full = 0;
	(*philo)->meals_eaten = 0;
	(*philo)->current_time = 0;
}

int	init_struct(t_main *main, t_args *args)
{
	int	i;

	i = 0;
	if (first_init(main, args))
		return (1);
	while (i < args->tot_phil)
	{
		main->philo[i] = malloc(sizeof(t_philo));
		if (!main->philo[i])
			return (1);
		main->philo[i]->philo = malloc(sizeof(pthread_t));
		if (!main->philo[i]->philo)
			return (1);
		main->philo[i]->no_philo = i + 1;
		main->philo[i]->mutex = main->mutex;
		main->philo[i]->args = args;
		main->philo[i]->start_time = main->start_time;
		set_struct_members_to_zero(&main->philo[i]);
		init_forks(main, args, i);
		i++;
	}
	main->philo[i] = NULL;
	return (0);
}
