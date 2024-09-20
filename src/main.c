/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:33:47 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/20 13:01:32 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_main	main;
	t_args	args;
	int		error_code;

	if (argc < 5 || argc > 6)
		return (init_errors(NULL, 1));
	if (init_time(&main))
		return (init_errors(NULL, 2));
	if (init_args(argc, argv, &args))
		return (init_errors(NULL, 3));
	if (init_struct(&main, &args))
		return (init_errors(&main, 4));
	error_code = simulation(&main, &args);
	if (error_code != 0)
		return (errors(&main, error_code));
	free_main_struct(&main);
	return (0);
}
