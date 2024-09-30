/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:31:27 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 14:56:25 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	long	current_time;

	current_time = time_elapsed_since_start(philo);
	mutex_action(&philo->mutex->print, LOCK);
	if (!philo_is_dead(philo))
		printf("%ld %d %s\n", current_time, philo->no_philo, message);
	mutex_action(&philo->mutex->print, UNLOCK);
}

void	print_death(t_philo *philo)
{
	long	current_time;

	current_time = time_elapsed_since_start(philo);
	mutex_action(&philo->mutex->print, LOCK);
	printf("%ld %d %s\n", current_time, philo->no_philo, "died");
	mutex_action(&philo->mutex->print, UNLOCK);
}
