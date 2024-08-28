/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:55:38 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/28 16:44:42 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->status);
	if (philo->args->someone_died)
	{
		pthread_mutex_unlock(&philo->mutex->status);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex->status);
	return (0);
}

void	print_message(t_philo *philo, char *message)
{
	philo->current_time = time_elapsed_since_start(philo);
	pthread_mutex_lock(&philo->mutex->print);
	if (!death(philo))
		printf("%ld %d %s\n", philo->current_time, philo->no_philo, message);
	pthread_mutex_unlock(&philo->mutex->print);
}

void	print_death(t_philo *philo)
{
	philo->current_time = time_elapsed_since_start(philo);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld %d %s\n", philo->current_time, philo->no_philo, "has died");
	pthread_mutex_unlock(&philo->mutex->print);
}

int	sleep_routine(t_philo *philo)
{
	if (death(philo))
		return (1);
	print_message(philo, "is sleeping");
	usleep(philo->args->t_to_sleep * 1000);
	if (death(philo))
		return (1);
	return (0);
}

int	eat_routine(t_philo *philo)
{
	if (death(philo))
		return (1);
	if (philo->forks[0] < philo->forks[1])
	{
		pthread_mutex_lock(&philo->mutex->fork[philo->forks[0]]);
		print_message(philo, "picked up a fork");
		pthread_mutex_lock(&philo->mutex->fork[philo->forks[1]]);
	}
	else if (philo->forks[0] > philo->forks[1])
	{
		pthread_mutex_lock(&philo->mutex->fork[philo->forks[1]]);
		print_message(philo, "picked up a fork");
		pthread_mutex_lock(&philo->mutex->fork[philo->forks[0]]);
	}
	print_message(philo, "picked up a fork");
	pthread_mutex_lock(&philo->mutex->eating);
	print_message(philo, "is eating");
	pthread_mutex_unlock(&philo->mutex->eating);
	timestamp_for_meal(philo);
	usleep(philo->args->t_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex->fork[philo->forks[0]]);
	pthread_mutex_unlock(&philo->mutex->fork[philo->forks[1]]);
	if (death(philo))
		return (1);
	return (0);
}

int	think_routine(t_philo *philo)
{
	print_message(philo, "is thinking");
	if (death(philo))
		return (1);
	return (0);
}

void	wait_for_all(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->start);
	philo->args->start++;
	pthread_mutex_unlock(&philo->mutex->start);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex->start);
		if (philo->args->start == philo->args->tot_phil)
		{
			pthread_mutex_unlock(&philo->mutex->start);
			return ;
		}
		pthread_mutex_unlock(&philo->mutex->start);
	}
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	philo->last_eaten = philo->start_time;
	i = 0;
	wait_for_all(philo);
	while (1)
	{
		if (philo->args->opt_arg && i == philo->args->amt_eat)
			break ;
		if (death(philo))
			break ;
		if (eat_routine(philo))
			break ;
		if (sleep_routine(philo))
			break ;
		if (think_routine(philo))
			break ;
		i++;
	}
	return (NULL);
}

void	*monitor_routine(void *ptr)
{
	int			i;
	t_monitor	*monitor;

	monitor = (t_monitor *)ptr;
	usleep(1000);
	while (1)
	{
		i = 0;
		while (monitor->main->philo[i])
		{
			if (time_elapsed_since_last_meal(monitor->main->philo[i]) > \
				monitor->main->philo[i]->args->t_to_die)
			{
				pthread_mutex_lock(&monitor->main->mutex->status);
				monitor->main->philo[i]->args->someone_died = 1;
				pthread_mutex_unlock(&monitor->main->mutex->status);
				print_death(monitor->main->philo[i]);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

t_monitor	*init_monitor(t_main *main, t_monitor *monitor)
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
	return (monitor);
}

int	philosophers(t_main *main, t_args *args)
{
	t_monitor	*monitor;
	int			i;

	i = 0;
	monitor = NULL;
	monitor = init_monitor(main, monitor);
	while (i < args->tot_phil)
	{
		if (pthread_create(main->philo[i]->philo, NULL, &philo_routine, \
		main->philo[i]) != 0)
			return (1);
		i++;
	}
	pthread_create(monitor->monitor, NULL, &monitor_routine, monitor);
	pthread_join(*monitor->monitor, NULL);
	i = 0;
	while (i < args->tot_phil)
	{
		if (pthread_join(*main->philo[i]->philo, NULL) != 0)
			return (2);
		i++;
	}
	free(monitor->monitor);
	free(monitor);
	return (0);
}
