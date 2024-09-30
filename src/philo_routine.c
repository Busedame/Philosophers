/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:55:38 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 14:26:46 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*lonely_philo(t_philo *philo)
{
	print_message(philo, "picked up a fork");
	usleep(philo->args->t_to_die * 1000);
	return (NULL);
}

int	sleep_routine(t_philo *philo)
{
	print_message(philo, "is sleeping");
	usleep(philo->args->t_to_sleep * 1000);
	return (0);
}

int	eat_routine(t_philo *philo)
{
	if (philo->no_philo % 2 != 0)
	{
		mutex_action(&philo->mutex->fork[philo->forks[0]], LOCK);
		print_message(philo, "picked up a fork");
		mutex_action(&philo->mutex->fork[philo->forks[1]], LOCK);
	}
	else
	{
		mutex_action(&philo->mutex->fork[philo->forks[1]], LOCK);
		print_message(philo, "picked up a fork");
		mutex_action(&philo->mutex->fork[philo->forks[0]], LOCK);
	}
	print_message(philo, "picked up a fork");
	mutex_action(&philo->mutex->eating, LOCK);
	print_message(philo, "is eating");
	mutex_action(&philo->mutex->eating, UNLOCK);
	timestamp_for_meal(philo);
	usleep(philo->args->t_to_eat * 1000);
	add_one_to_long(&philo->mutex->philo[philo->no_philo - 1], \
	&philo->meals_eaten);
	mutex_action(&philo->mutex->fork[philo->forks[0]], UNLOCK);
	mutex_action(&philo->mutex->fork[philo->forks[1]], UNLOCK);
	if (is_philo_full(philo))
		return (1);
	return (0);
}

int	think_routine(t_philo *philo)
{
	print_message(philo, "is thinking");
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], LOCK);
	if (philo->no_philo % 2 != 0)
		usleep(500);
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
	return (0);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	bool	end_simulation;

	philo = (t_philo *)ptr;
	end_simulation = false;
	set_long((&philo->mutex->philo[philo->no_philo - 1]), \
	&philo->last_eaten, philo->start_time);
	if (philo->args->tot_phil == 1)
		return (lonely_philo(philo));
	while (!end_simulation && !philo_is_dead(philo))
	{
		if (eat_routine(philo))
			end_simulation = true;
		if (sleep_routine(philo))
			break ;
		if (think_routine(philo))
			break ;
	}
	return (NULL);
}
