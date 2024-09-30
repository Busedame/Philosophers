/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:55:38 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 17:05:55 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Prints a message saying the philosopher picked up a fork.
Then calls usleep to sleep for time_to_die milliseconds, before it prints
that the philosopher died. It is hardcoded, but there is also nothing
else that could potentially happen.*/
static void	*lonely_philo(t_philo *philo)
{
	print_message(philo, "picked up a fork");
	usleep(philo->args->t_to_die * 1000);
	print_death(philo);
	return (NULL);
}

/*Prints a message saying the philosopher is sleeping.
Calls the usleep-function to sleep for the specified time.*/
int	sleep_routine(t_philo *philo)
{
	print_message(philo, "is sleeping");
	usleep(philo->args->t_to_sleep * 1000);
	return (0);
}

/*If the philosopher is odd numbered, it tries to pick its left fork first,
and then the right one. If the philosopher is even numbered, it tries to pick
its right fork first, and then the left one.
This is a common approach in the Philosophers dining problem, as it ensures
no deadlocks are happening, and proper synchronization.
Once a philosopher has both forks, they eat for a specified amount of time.
The timestamp for the beginning of their meal is saved, and also the
amount of meals they have eaten. If the philosopher is full, the function
returns 1. Otherwise, it returns 0.*/
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

/*Prints a message saying the philosopher is thinking.
Also sleeps for 500 microseconds if the philosopher is odd, to ensure
better synchronization. This way the fight for forks will be decreased.*/
int	think_routine(t_philo *philo)
{
	print_message(philo, "is thinking");
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], LOCK);
	if (philo->no_philo % 2 != 0)
		usleep(500);
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
	return (0);
}

/*The philosopher threads routine.
Before while-loop:
- Sets the last_eaten variable to the start_time of the program.
- If there is only one philosopher, it has its own routine.
The while loop goes on until the philosopher is full, or if someone died.
The philosophers alternate between eating, sleeping and thinking for
specified time intervals.
@param end_simulation Gets set to true if a philosopher is full.*/
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
