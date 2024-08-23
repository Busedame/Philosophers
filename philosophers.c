/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:55:38 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/23 16:52:05 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->mutex->print);
	pthread_mutex_lock(&philo->mutex->fork[philo->forks[0]]);
	printf("Philosopher %d has picked up fork %d with his right hand\n", philo->no_philo, philo->forks[0]);
	pthread_mutex_lock(&philo->mutex->fork[philo->forks[1]]);
	printf("Philosopher %d has picked up fork %d with his left hand\n", philo->no_philo, philo->forks[1]);
	printf("Philosopher %d is eating\n", philo->no_philo);
	printf("Philosopher %d puts down fork %d\n", philo->no_philo, philo->forks[0]);
	printf("Philosopher %d puts down fork %d\n", philo->no_philo, philo->forks[1]);
	pthread_mutex_unlock(&philo->mutex->fork[philo->forks[0]]);
	pthread_mutex_unlock(&philo->mutex->fork[philo->forks[1]]);
	pthread_mutex_unlock(&philo->mutex->print);
	return (NULL);
}

int	philosophers(t_main *main, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->tot_phil)
	{
		if (pthread_create(main->philo[i]->philo, NULL, &routine, main->philo[i]) != 0)
			printf("Error\n");
		i++;
	}
	i = 0;
	while (i < args->tot_phil)
	{
		if (pthread_join(*main->philo[i]->philo, NULL) != 0)
			printf("Error\n");
		i++;
	}
	return (0);
}
