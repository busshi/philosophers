/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 18:57:31 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/25 18:58:26 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(t_philo *philo, long nb_philo)
{
	long	i;

	if (philo[0].display)
	{
		pthread_mutex_destroy(philo[0].display);
		free(philo[0].display);
		philo[0].display = NULL;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&philo[0].forks[i]);
		i++;
	}
}

int	free_data(t_data *data)
{
	if (data)
	{
		free(data);
		data = NULL;
	}
	return (FAILURE);
}

int	free_philo(t_data *data, t_philo *philo)
{
	if (philo[0].state)
	{
		free(philo[0].state);
		philo[0].state = NULL;
	}
	if (philo[0].philo_full)
	{
		free(philo[0].philo_full);
		philo[0].philo_full = NULL;
	}
	if (philo[0].forks)
	{
		free(philo[0].forks);
		philo[0].forks = NULL;
	}
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
	free_data(data);
	return (FAILURE);
}
