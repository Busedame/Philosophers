/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:42:00 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/23 15:21:27 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_digitcount(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_conversion(char *nptr, long n, int end)
{
	int	start;

	start = 0;
	if (n < 0)
	{
		nptr[start] = '-';
		n *= -1;
		start = 1;
	}
	nptr[end] = '\0';
	end--;
	while (end >= start)
	{
		nptr[end] = n % 10 + '0';
		n = n / 10;
		end--;
	}
	return (nptr);
}

char	*ft_itoa(int n)
{
	char	*nptr;
	int		digcount;

	digcount = ft_digitcount((long) n);
	if (n == 0)
	{
		nptr = (char *)malloc(2);
		if (!nptr)
			return (NULL);
		nptr[0] = '0';
		nptr[1] = '\0';
		return (nptr);
	}
	nptr = (char *)malloc(sizeof(char) * digcount + 1);
	if (!nptr)
		return (NULL);
	nptr = ft_conversion(nptr, (long) n, digcount);
	return (nptr);
}
