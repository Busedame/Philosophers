/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:33:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/21 20:29:11 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	test = 0;

void	*routine(void *ptr)
{
	test++;
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	int		i;

	if (argc != 2)
		return (1);
	i = 0;
	philo.no_philo = atoi(argv[1]);
	philo.philo = malloc(sizeof(pthread_t) * (philo.no_philo + 1));
	if (!philo.philo)
		return (2);
	while (i < philo.no_philo)
		pthread_create(&philo.philo[i++], NULL, &routine, NULL);
	i = 0;
	while (i < philo.no_philo)
		pthread_join(philo.philo[i++], NULL);
	printf("%d\n", test);
	return (0);
}
