/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:44:51 by nholbroo          #+#    #+#             */
/*   Updated: 2024/10/02 15:38:11 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Checks if all the program arguments are numerical.*/
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

/*Checks if arguments are valid, stores the program arguments in the
t_args struct, plus initializes all the other members of the struct to 0.*/
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
	args->t_to_think = (args->t_to_die - args->t_to_eat - args->t_to_sleep) / 2;
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
