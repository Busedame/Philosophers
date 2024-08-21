/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_process_diff.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:02:39 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/21 15:31:47 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// You can have several threads inside one process.
// A value modified in one process will not affect the value in other processes.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	x = 2;

void	*routine2(void)
{
	x += 5;
	sleep(2);
	printf("Value of x: %d\n", x);
}

void	*routine(void)
{
	x += 5;
	sleep(2);
	printf("Value of x: %d\n", x);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (3);
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	int	pid;
// 	int	x;

// 	pid = fork();
// 	x = 2;
// 	printf("%d\n", getpid());
// 	if (!pid)
// 	{
// 		x++;
// 		printf("Value of x: %d\n", x);
// 	}
// 	if (pid != 0)
// 	{
// 		printf("Value of x: %d\n", x);
// 		wait(NULL);
// 	}
// 	return (0);
// }
