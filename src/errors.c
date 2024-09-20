/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:53:40 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/20 10:59:37 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	errors(t_main *main, int error_code)
{
	ft_putstr_fd(BOLD, 2);
	if (error_code == 1)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(THREAD_INIT_ERR, 2);
	}
	if (error_code == 2)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(THREAD_REMOVE_ERR, 2);
	}
	ft_putstr_fd(RESET, 2);
	free_main_struct(main);
	return (error_code);
}

int	init_errors(t_main *main, int error_code)
{
	ft_putstr_fd(BOLD, 2);
	if (error_code == 1)
	{
		ft_putstr_fd(YELLOW, 2);
		ft_putstr_fd(USAGE_ERR, 2);
	}
	if (error_code == 2)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(TIME_ERR, 2);
	}
	if (error_code == 3)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(INPUT_ERR, 2);
	}
	if (error_code == 4)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(INIT_ERR, 2);
	}
	ft_putstr_fd(RESET, 2);
	free_main_struct(main);
	return (error_code);
}
