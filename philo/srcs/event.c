/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:55:07 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/27 18:05:05 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_state(t_philo *philo, enum e_state state)
{
	pthread_mutex_lock(philo->display);
	if (state == TAKING_FORK)
		print_event(philo, FORK);
	if (state == EATING)
		print_event(philo, EAT);
	if (state == SLEEPING)
		print_event(philo, SLEEP);
	if (state == THINKING)
		print_event(philo, THINK);
	if (state == DEAD)
	{
		print_event(philo, DEATH);
		*philo->stop = PHILO_DEAD;
	}
	pthread_mutex_unlock(philo->display);
}

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right);
		change_state(philo, TAKING_FORK);
		if (philo->data->nb_philo == 1)
		{
			while (*philo->stop != PHILO_DEAD)
				ft_usleep(100);
			pthread_mutex_unlock(philo->right);
			return ;
		}
		pthread_mutex_lock(philo->left);
		change_state(philo, TAKING_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		change_state(philo, TAKING_FORK);
		pthread_mutex_lock(philo->left);
		change_state(philo, TAKING_FORK);
	}
}

void	is_eating(t_philo *philo)
{
	if (philo->data->nb_eat_max != -1
		&& philo->nb_eat == philo->data->nb_eat_max)
		return ;
	taking_forks(philo);
	if (*philo->stop == PHILO_DEAD)
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		return ;
	}
	change_state(philo, EATING);
	philo->last_eat = calculate_ts();
	philo->nb_eat++;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	is_sleeping(t_philo *philo)
{
	change_state(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	change_state(philo, THINKING);
}
