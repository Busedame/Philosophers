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

void	sleep_routine(t_philo *philo)
{
	long	elapsed_time;

	elapsed_time = 0;
	while (elapsed_time != philo->args->t_to_sleep)
		elapsed_time = time_elapsed_since_last_meal(philo);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld Philosopher %d is sleeping\n", elapsed_time, philo->no_philo);
	pthread_mutex_unlock(&philo->mutex->print);
	usleep(philo->args->t_to_sleep * 1000);
}

void	eat_routine_even(t_philo *philo)
{
	long	elapsed_time;

	elapsed_time = 0;
	while (elapsed_time != philo->args->t_to_eat)
		elapsed_time = time_elapsed_since_last_meal(philo);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld Philosopher %d has taken a fork\n", elapsed_time, philo->no_philo);
	pthread_mutex_unlock(&philo->mutex->print);
	pthread_mutex_lock(&philo->mutex->fork[philo->forks[0]]);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld Philosopher %d has taken a fork\n", elapsed_time, philo->no_philo);
	pthread_mutex_unlock(&philo->mutex->print);
	pthread_mutex_lock(&philo->mutex->fork[philo->forks[1]]);
	philo->last_eaten = get_current_time(philo);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld Philosopher %d is eating\n", elapsed_time, philo->no_philo);
	pthread_mutex_unlock(&philo->mutex->print);
	pthread_mutex_unlock(&philo->mutex->fork[philo->forks[0]]);
	pthread_mutex_unlock(&philo->mutex->fork[philo->forks[1]]);
	usleep(philo->args->t_to_eat * 1000);
}

void	eat_routine_odd(t_philo *philo)
{
	long	elapsed_time;

	elapsed_time = 0;
	while (elapsed_time != philo->args->t_to_eat)
		elapsed_time = time_elapsed_since_last_meal(philo);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld Philosopher %d has taken a fork\n", elapsed_time, philo->no_philo);
	pthread_mutex_unlock(&philo->mutex->print);
	pthread_mutex_lock(&philo->mutex->fork[philo->forks[1]]);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld Philosopher %d has taken a fork\n", elapsed_time, philo->no_philo);
	pthread_mutex_unlock(&philo->mutex->print);
	pthread_mutex_lock(&philo->mutex->fork[philo->forks[0]]);
	philo->last_eaten = get_current_time(philo);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld Philosopher %d is eating\n", elapsed_time, philo->no_philo);
	pthread_mutex_unlock(&philo->mutex->print);
	pthread_mutex_unlock(&philo->mutex->fork[philo->forks[1]]);
	pthread_mutex_unlock(&philo->mutex->fork[philo->forks[0]]);
	usleep(philo->args->t_to_eat * 1000);
}

void	eat_routine(t_philo *philo)
{
	long	current_time;

	current_time = get_current_time(philo);
	if (current_time - philo->last_eaten > philo->args->t_to_die)
		printf("Philosopher %d died\n", philo->no_philo);
	if (philo->no_philo % 2)
		eat_routine_even(philo);
	else
		eat_routine_odd(philo);
}

void	think_routine(t_philo *philo)
{
	long	current_time;

	current_time = get_current_time(philo);
	pthread_mutex_lock(&philo->mutex->print);
	printf("%ld Philosopher %d is thinking\n", current_time, philo->no_philo);
	pthread_mutex_unlock(&philo->mutex->print);
	usleep(500);
}

void	*routine(void *ptr)
{
	t_philo	*philo;
	long	elapsed_time;

	philo = (t_philo *)ptr;
	philo->last_eaten = philo->start_time;
	elapsed_time = 0;
	if (philo->no_philo % 2)
		usleep(100);
	while (1)
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
		elapsed_time = get_current_time(philo);
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
