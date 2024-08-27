/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:55:38 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/27 15:15:49 by nholbroo         ###   ########.fr       */
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
	if (philo->no_philo % 2)
		pthread_mutex_lock(&philo->mutex->fork[philo->forks[0]]);
	else
		pthread_mutex_lock(&philo->mutex->fork[philo->forks[1]]);
	print_message(philo, "has taken a fork");
	if (philo->no_philo % 2)
		pthread_mutex_lock(&philo->mutex->fork[philo->forks[1]]);
	else
		pthread_mutex_lock(&philo->mutex->fork[philo->forks[0]]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->mutex->eating);
	print_message(philo, "is eating");
	pthread_mutex_ulock(&philo->mutex->eating);
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
	if (!death(philo))
		print_message(philo, "is thinking");
	if (death(philo))
		return (1);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	philo->last_eaten = philo->start_time;
	i = 0;
	while (1)
	{
		if (death(philo))
			break ;
		if (time_elapsed_since_last_meal(philo) > philo->args->t_to_die)
		{
			pthread_mutex_lock(&philo->mutex->status);
			philo->args->someone_died = 1;
			pthread_mutex_unlock(&philo->mutex->status);
			print_death(philo);
			break ;
		}
		if (eat_routine(philo))
			break ;
		if (sleep_routine(philo))
			break ;
		if (think_routine(philo))
			break ;
		i++;
		if (philo->args->opt_arg && i == philo->args->amt_eat)
			break ;
	}
	return (NULL);
}

int	philosophers(t_main *main, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->tot_phil)
	{
		if (pthread_create(main->philo[i]->philo, NULL, &routine, \
		main->philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < args->tot_phil)
	{
		if (pthread_join(*main->philo[i]->philo, NULL) != 0)
			return (2);
		i++;
	}
	return (0);
}
