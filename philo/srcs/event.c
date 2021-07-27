/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 17:55:07 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/27 16:29:45 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_state(t_philo *philo, enum e_status status)
{
	if (status == EATING || status == SLEEPING || status == THINKING
		|| status == DIE || status == FUL)
		philo->status = status;
	if (status == FUL)
	{
		*philo->state = FULL;
		return ;
	}
	pthread_mutex_lock(philo->display);
	if (status == EATING)
		print_event(philo, EAT);
	if (status == SLEEPING)
		print_event(philo, SLEEP);
	if (status == THINKING)
		print_event(philo, THINK);
	if (status == DIE)
	{
		print_event(philo, DEATH);
		*philo->state = DEAD;
	}
	pthread_mutex_unlock(philo->display);
}

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(philo->display);
		print_event(philo, FORK);
		pthread_mutex_unlock(philo->display);
		if (philo->data->nb_philo == 1)
		{
			while (*philo->state != DEAD)
				ft_usleep(100);
			pthread_mutex_unlock(philo->right);
			return ;
		}
		else
		{
			pthread_mutex_lock(philo->left);
			pthread_mutex_lock(philo->display);
			print_event(philo, FORK);
			pthread_mutex_unlock(philo->display);
		}
	}
	else
	{
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(philo->display);
		print_event(philo, FORK);
		pthread_mutex_unlock(philo->display);
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->display);
		print_event(philo, FORK);
		pthread_mutex_unlock(philo->display);
	}
}

void	is_eating(t_philo *philo)
{
	if (philo->data->nb_eat_max != -1
		&& philo->nb_eat == philo->data->nb_eat_max)
		return ;
	taking_forks(philo);
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
