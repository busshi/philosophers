/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:21:50 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/23 16:28:44 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	calculate_ts(void)
{
	struct timeval	ts;

	gettimeofday(&ts, NULL);
	return (ts.tv_sec * 1000 + ts.tv_usec / 1000);
}

void	ft_usleep(unsigned long long ms)
{
	unsigned long long	current;
	unsigned long long	end;

	end = calculate_ts() + ms;
	current = 0;
	while (current < end)
	{
		current = calculate_ts();
		usleep(10);
	}
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long long	ft_atoi_long(const char *nptr)
{
	size_t		i;
	size_t		sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == '\n' || nptr[i] == ' ' || nptr[i] == '\f'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}
