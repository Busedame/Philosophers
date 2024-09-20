/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:44:51 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/20 10:52:10 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char **argv)
{
	int	i;
	int	str;

	str = 1;
	while (str < argc)
	{
		i = 0;
		while (argv[str][i] != '\0')
		{
			if (argv[str][i] < '0' || argv[str][i] > '9')
				return (1);
			i++;
		}
		str++;
	}
	return (0);
}

int	init_args(int argc, char **argv, t_args *args)
{
	if (check_args(argc, argv))
		return (1);
	args->tot_phil = ft_atol(argv[1]);
	args->t_to_die = ft_atol(argv[2]);
	args->t_to_eat = ft_atol(argv[3]);
	args->t_to_sleep = ft_atol(argv[4]);
	args->someone_died = 0;
	args->max_eat = 0;
	args->opt_arg = false;
	args->all_philos_full = false;
	if (argc == 6)
	{
		args->max_eat = ft_atol(argv[5]);
		args->opt_arg = 1;
	}
	if ((args->opt_arg && args->max_eat < 0) || args->tot_phil <= 0 
		|| args->t_to_die < 0 || args->t_to_eat < 0
		|| args->t_to_sleep < 0)
		return (1);
	return (0);
}
