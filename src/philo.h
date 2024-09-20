/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:32:39 by nholbroo          #+#    #+#             */
/*   Updated: 2024/09/20 13:02:37 by nholbroo         ###   ########.fr       */
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

typedef enum s_action
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
}	t_action;

typedef struct s_args
{
	long	tot_phil;
	long	t_to_die;
	long	t_to_eat;
	long	t_to_sleep;
	long	max_eat;
	bool	opt_arg;
	bool	someone_died;
	bool	all_philos_full;
	long	start_time;
}	t_args;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*philo;
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
	long			meals_eaten;
	bool			full;
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
long		ft_atol(const char *nptr);
void		ft_putstr_fd(char *s, int fd);

// Inits:
int			init_args(int argc, char **argv, t_args *args);
int			init_struct(t_main *main, t_args *args);
t_monitor	*init_and_start_monitor(t_main *main, t_monitor *monitor);

// Mutexes, bools and longs:
int			mutex_action(pthread_mutex_t *mutex, int action);
bool		get_bool(pthread_mutex_t *mutex, bool *status);
void		set_bool(pthread_mutex_t *mutex, bool *status, bool new_status);
long		get_long(pthread_mutex_t *mutex, long value);
void		set_long(pthread_mutex_t *mutex, long *value, long new_value);
void		add_one_to_long(pthread_mutex_t *mutex, long *value);

// Time:
int			init_time(t_main *main);
long		time_elapsed_since_last_meal(t_philo *philo);
long		time_elapsed_since_start(t_philo *philo);
int			timestamp_for_meal(t_philo *philo);
long		get_current_time(void);

// Printing:
void		print_death(t_philo *philo);

// Philosophers:
int			simulation(t_main *main, t_args *args);
void		*philo_routine(void *ptr);
void		*monitor_routine(void *ptr);
int			is_philo_full(t_philo *philo);
int			philo_is_dead(t_philo *philo);
void		print_message(t_philo *philo, char *message);
void		print_death(t_philo *philo);

// Freeing allocated memory:
void		free_main_struct(t_main *main);
int			free_monitor(t_monitor *monitor, bool error);

// Errors:
int			init_errors(t_main *main, int error_code);
int			errors(t_main *main, int error_code);

#endif