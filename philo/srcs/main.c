/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:09:22 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/27 17:26:40 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*death_monitor(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while (*philo->stop != PHILO_DEAD && *philo->stop != PHILO_FULL)
	{
		if ((long)calculate_ts() - (long)philo->last_eat
			>= philo->data->time_to_die)
			change_state(philo, DEAD);
		usleep(100);
	}
	return (philo);
}

void	*routine(void *tmp)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = (t_philo *)tmp;
	if (pthread_create(&monitor, NULL, &death_monitor, philo) != 0)
	{
		fatal_error(THREAD_CREATE);
		return ((void *)1);
	}
	pthread_detach(monitor);
	while (*philo->stop != PHILO_DEAD && *philo->stop != PHILO_FULL)
	{
		is_eating(philo);
		if (philo->data->nb_eat_max != -1
			&& philo->nb_eat == philo->data->nb_eat_max)
			(*philo->philo_full)++;
		if (*philo->philo_full == philo->data->nb_philo)
		{
			*philo->stop = PHILO_FULL;
			break ;
		}
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (philo);
}

void	philo_start(t_philo *philo, long nb_philo)
{
	long	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (fatal_error(THREAD_CREATE));
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (fatal_error(THREAD_CREATE));
		i += 2;
	}
}

static void	philo_end(t_data *data, t_philo *philo)
{
	long		i;

	i = 0;
	ft_usleep(1000);
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (*philo->stop == PHILO_DEAD)
		printf("%sphilo: one philo is dead!!\n%s", RED, CLEAR);
	if (data->nb_eat_max != -1 && *philo->stop == PHILO_FULL)
		printf("%sphilo: philosophers are full!\n%s", GREEN, CLEAR);
	free_mutex(philo, data->nb_philo);
	free_philo(data, philo);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	if (ac < 5 || ac > 6)
		return (exit_error(BAD_ARGUMENTS));
	data = init_data(ac, av);
	if (data)
	{
		philo = init(data);
		if (!philo)
			return (free_data(data));
		if (init_display_mutex(data, philo) == FAILURE)
			return (free_philo(data, philo));
		philo_start(philo, data->nb_philo);
		philo_end(data, philo);
	}
	return (SUCCESS);
}
