/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:33:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/23 16:56:11 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_main	main;
	t_args	args;

	if (argc < 5 || argc > 6)
		return (init_errors(NULL, 1));
	if (init_args(argc, argv, &args))
		return (init_errors(NULL, 2));
	if (init_struct(&main, &args))
		return (init_errors(&main, 3));
	if (philosophers(&main, &args))
		return (4);
	free_main_struct(&main);
	return (0);
}
