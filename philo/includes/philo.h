/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:08:38 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/27 17:27:02 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include "constants.h"

typedef struct s_data
{
	long	nb_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_eat_max;
	long	start;
}		t_data;

typedef struct s_philo
{
	t_data			*data;
	long			id;
	pthread_t		thread;
	long			nb_eat;
	enum e_stop		*stop;
	long			last_eat;
	long			*philo_full;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	*display;
}				t_philo;

t_data		*init_data(int ac, char **av);
t_philo		*init(t_data *data);
int			init_display_mutex(t_data *data, t_philo *philo);
void		change_state(t_philo *philo, enum e_state state);
int			exit_error(enum e_error error);
void		fatal_error(enum e_error error);
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
long long	ft_atoi_long(const char *nptr);
void		print_event(t_philo *philo, const char *event);
void		is_eating(t_philo *philo);
void		is_sleeping(t_philo *philo);
void		is_thinking(t_philo *philo);
void		ft_usleep(unsigned long long md);
long		calculate_ts(void);
void		free_mutex(t_philo *philo, long nb_philo);
int			free_data(t_data *data);
int			free_philo(t_data *data, t_philo *philo);

#endif
