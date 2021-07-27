/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 22:48:43 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/25 18:19:23 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_positive_nb(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	check_overflow(char *s)
{
	long long	nb;

	nb = ft_atoi_long(s);
	if (nb >= 0 && nb <= LONG_MAX)
		return (nb);
	return (ERROR);
}

static int	check_arg(char *av)
{
	long	ret;

	ret = check_overflow(av);
	if (ret >= 0 && is_positive_nb(av))
		return (ret);
	return (ERROR);
}

static int	check_data(int ac, t_data *data)
{
	if (data->nb_philo < 1)
	{
		exit_error(NB_PHILO);
		free(data);
		data = NULL;
		return (FALSE);
	}
	else if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || (ac == 6 && data->nb_eat_max < 0))
	{
		exit_error(BAD_NUMBER);
		free(data);
		data = NULL;
		return (FALSE);
	}
	return (TRUE);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_philo = check_arg(av[1]);
	data->time_to_die = check_arg(av[2]);
	data->time_to_eat = check_arg(av[3]);
	data->time_to_sleep = check_arg(av[4]);
	data->nb_eat_max = -1;
	data->start = calculate_ts();
	if (ac == 6)
		data->nb_eat_max = check_arg(av[5]);
	if (check_data(ac, data))
		return (data);
	else
		return (NULL);
}
