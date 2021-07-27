/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 15:28:22 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/26 17:16:42 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_display_mutex(t_data *data, t_philo *philo)
{
	long			i;
	pthread_mutex_t	*display;

	display = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!display)
		return (exit_error(MALLOC_FAIL));
	if (pthread_mutex_init(display, NULL) != 0)
	{
		pthread_mutex_destroy(display);
		free(display);
		return (exit_error(MUTEX_INIT));
	}
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].display = display;
		i++;
	}
	return (SUCCESS);
}

static void	init_forks(t_philo *philo, int nb_philo)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!forks)
		return ;
	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < nb_philo)
	{
		philo[i].forks = forks;
		philo[i].left = &philo->forks[i];
		if (!i)
			philo[i].right = &philo->forks[nb_philo - 1];
		else
			philo[i].right = &philo->forks[i - 1];
		i++;
	}
}

static t_philo	*init_philo(t_data *data, enum e_state *state, long *full)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].state = state;
		if (data->nb_eat_max == 0)
			*philo[i].state = FULL;
		else
			*philo[i].state = ALIVE;
		philo[i].status = THINKING;
		philo[i].id = i + 1;
		philo[i].nb_eat = 0;
		philo[i].last_eat = calculate_ts();
		philo[i].philo_full = full;
		i++;
	}
	init_forks(philo, data->nb_philo);
	return (philo);
}

static void	*fail_init_philo(enum e_state *state, long *full)
{
	free(full);
	full = NULL;
	free(state);
	state = NULL;
	fatal_error(MALLOC_FAIL);
	return (NULL);
}

t_philo	*init(t_data *data)
{
	t_philo			*philo;
	enum e_state	*state;
	long			*full;

	state = (enum e_state *)malloc(sizeof(enum e_state));
	if (!state)
	{
		fatal_error(MALLOC_FAIL);
		return (NULL);
	}
	full = (long *)malloc(sizeof(long));
	if (!full)
	{
		free(state);
		fatal_error(MALLOC_FAIL);
		return (NULL);
	}
	*full = 0;
	philo = init_philo(data, state, full);
	if (!philo)
		return (fail_init_philo(state, full));
	return (philo);
}
