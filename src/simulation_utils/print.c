/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:31:27 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 15:40:19 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Prints a message in the format specified by the Philosophers project.
Format: <timestamp_in_ms> <philo_no> <action>
E.g. 0 2 picked up a fork.
The printing is protected by a mutex, to avoid race conditions in the case
of several threads wanting to print at once.*/
void	print_message(t_philo *philo, char *message)
{
	long	current_time;

	current_time = time_elapsed_since_start(philo);
	mutex_action(&philo->mutex->print, LOCK);
	if (!philo_is_dead(philo))
		printf("%ld %d %s\n", current_time, philo->no_philo, message);
	mutex_action(&philo->mutex->print, UNLOCK);
}

/*Prints a death message in the format specified by the Philosophers project.
There is a separate print_death function because in the case of a philosopher
dying, this should still be printed - but no other actions - like eating, 
sleeping, etc. 
Format: <timestamp_in_ms> <philo_no> <action>
E.g. 0 2 died.
The printing is protected by a mutex, to avoid race conditions in the case
of several threads wanting to print at once.*/
void	print_death(t_philo *philo)
{
	long	current_time;

	current_time = time_elapsed_since_start(philo);
	mutex_action(&philo->mutex->print, LOCK);
	printf("%ld %d %s\n", current_time, philo->no_philo, "died");
	mutex_action(&philo->mutex->print, UNLOCK);
}
