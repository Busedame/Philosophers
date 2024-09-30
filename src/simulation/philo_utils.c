/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:01:58 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/30 13:51:22 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_philo *philo)
{
	if (get_bool(&philo->mutex->status, &philo->args->someone_died))
		return (1);
	return (0);
}

int	is_philo_full(t_philo *philo)
{
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], LOCK);
	if (philo->args->opt_arg && philo->meals_eaten == philo->args->max_eat)
	{
		philo->full = true;
		mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
		return (1);
	}
	mutex_action(&philo->mutex->philo[philo->no_philo - 1], UNLOCK);
	return (0);
}
