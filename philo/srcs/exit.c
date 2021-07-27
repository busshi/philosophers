/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 22:49:33 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/23 18:37:14 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_str(const char *s)
{
	write(STDERR_FILENO, s, ft_strlen(s));
}

int	exit_error(enum e_error err)
{
	if (err == BAD_ARGUMENTS)
	{
		error_str("philo: Wrong number of arguments\n");
		error_str("Usage: ./philo nb_of_philo time_to_die time_to_eat ");
		error_str("time_to_sleep [nb_of_times_each_philosoopher_must_eat]\n");
	}
	else if (err == BAD_NUMBER)
		error_str("philo: Wrong argument! Only positives integers are valid!\n");
	else if (err == NB_PHILO)
		error_str("philo: Minimum 1 philo is required!\n");
	else if (err == MALLOC_FAIL)
		error_str("philo: Fail to allocate memory\n");
	else if (err == THREAD_CREATE)
		error_str("philo: Fail to create a thread\n");
	else if (err == MUTEX_INIT)
		error_str("philo: Fail to initialize a mutex\n");
	return (ERROR);
}

void	fatal_error(enum e_error err)
{
	exit_error(err);
}
