/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:17:24 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/23 16:55:34 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_main_struct(t_main *main)
{
	int	i;

	if (main)
	{
		if (main->philo)
		{
			i = 0;
			while (main->philo[i])
			{
				if (main->philo[i]->philo)
					free(main->philo[i]->philo);
				free(main->philo[i]);
				i++;
			}
			free(main->philo);
		}
		if (main->mutex)
		{
			if (main->mutex->fork)
				free(main->mutex->fork);
			free(main->mutex);
		}
	}
}
