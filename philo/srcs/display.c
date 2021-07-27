/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 16:51:25 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/27 17:24:01 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	len_nb(long n)
{
	size_t	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_itoa(long n)
{
	char	*s;
	size_t	len;

	len = len_nb(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len] = '\0';
	while (len > 0)
	{
		len--;
		s[len] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}

static char	*ft_strjoin(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*join;

	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (join);
}

static void	write_event(long timestamp, long id, const char *event)
{
	char	*buf;
	char	*tmp;

	buf = ft_itoa(timestamp);
	buf = ft_strjoin(buf, " ");
	tmp = ft_itoa(id);
	buf = ft_strjoin(buf, tmp);
	free(tmp);
	buf = ft_strjoin(buf, " ");
	buf = ft_strjoin(buf, event);
	buf = ft_strjoin(buf, "\n");
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	free(buf);
}

void	print_event(t_philo *philo, const char *event)
{
	long	timestamp;

	if (*philo->stop == PHILO_DEAD
		|| (philo->data->nb_eat_max == 0 && *philo->stop == PHILO_FULL))
		return ;
	timestamp = calculate_ts() - philo->data->start;
	write_event(timestamp, philo->id, event);
}
