/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:32:39 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/23 15:58:44 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stddef.h>
# include <stdbool.h>
# define USAGE_ERR	"Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define INPUT_ERR	"Arguments must be numerical and positive\n"
# define INIT_ERR	"Failure initializing the main struct\n"


typedef struct s_args
{
	int		tot_phil;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		amt_eat;
	bool	opt_arg;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		*philo;
	int				no_philo;
	unsigned int	forks[2];
	t_mutex			*mutex;
	t_args			*args;
}	t_philo;

typedef struct s_main
{
	t_philo			**philo;
	t_mutex			*mutex;
}	t_main;


// Standard functions:
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

// Inits:
int		init_args(int argc, char **argv, t_args *args);
int		init_struct(t_main *main, t_args *args);

// Philosophers:
int		philosophers(t_main *main, t_args *args);

// Freeing allocated memory:
void	free_main_struct(t_main *main);

// Errors:
int		init_errors(t_main *main, int error_code);

#endif