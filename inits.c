/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:13:01 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/26 18:30:35 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_main *main, t_args *args)
{
	int	i;
	int	phil;

	i = 0;
	main->mutex = malloc(sizeof(t_mutex));
	if (!main->mutex)
		return (1);
	main->mutex->fork = malloc(sizeof(pthread_mutex_t) * (args->tot_phil + 1));
	if (!main->mutex->fork)
		return (1);
	pthread_mutex_init(&main->mutex->print, NULL);
	pthread_mutex_init(&main->mutex->status, NULL);
	pthread_mutex_init(&main->mutex->eating, NULL);
	while (i <= args->tot_phil)
	{
		if (pthread_mutex_init(&main->mutex->fork[i], NULL) != 0)
			return (1);
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
		main->philo[i]->forks[0] = args->tot_phil;
	else
		main->philo[i]->forks[0] = main->philo[i]->no_philo - 1;
	main->philo[i]->forks[1] = main->philo[i]->no_philo;
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
		main->philo[i]->last_eaten = 0;
		init_forks(main, args, i);
		i++;
	}
	main->philo[i] = NULL;
	return (0);
}
