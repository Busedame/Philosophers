/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:32:39 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/28 16:42:30 by nholbroo         ###   ########.fr       */
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
# include <string.h>
# include <sys/time.h>
# define BOLD			"\033[1m"
# define RED			"\033[31;2m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define RESET			"\033[0m"
# define USAGE_ERR	"Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define TIME_ERR	"Error: gettimeofday-function failed\n"
# define INPUT_ERR	"Error: Arguments must be numerical and positive\n"
# define INIT_ERR	"Error: Failure initializing the main struct\n"
# define THREAD_INIT_ERR	"Error: Failed to create thread\n"
# define THREAD_REMOVE_ERR	"Error: Failed to remove thread\n"

typedef struct s_args
{
	int		tot_phil;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		amt_eat;
	bool	opt_arg;
	bool	someone_died;
	int		start;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	status;
	pthread_mutex_t	eating;
	pthread_mutex_t	start;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		*philo;
	int				no_philo;
	unsigned int	forks[2];
	long			start_time;
	long			current_time;
	long			last_eaten;
	t_mutex			*mutex;
	t_args			*args;
}	t_philo;

typedef struct s_main
{
	t_philo			**philo;
	t_mutex			*mutex;
	long			start_time;
}	t_main;

typedef struct s_monitor
{
	pthread_t	*monitor;
	t_main		*main;
}	t_monitor;


// Standard functions:
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

// Inits:
int		init_args(int argc, char **argv, t_args *args);
int		init_struct(t_main *main, t_args *args);

// Time:
int		init_time(t_main *main);
long	time_elapsed_since_last_meal(t_philo *philo);
long	time_elapsed_since_start(t_philo *philo);
int		timestamp_for_meal(t_philo *philo);
long	get_current_time(t_philo *philo);

// Printing:
void	print_death(t_philo *philo);

// Philosophers:
int		philosophers(t_main *main, t_args *args);

// Freeing allocated memory:
void	free_main_struct(t_main *main);

// Errors:
int		init_errors(t_main *main, int error_code);
int		errors(t_main *main, int error_code);

#endif