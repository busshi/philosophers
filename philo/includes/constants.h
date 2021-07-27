/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:57:05 by aldubar           #+#    #+#             */
/*   Updated: 2021/07/26 11:07:00 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define SUCCESS	0
# define FAILURE	1
# define TRUE	1
# define FALSE	0
# define ERROR	-1
# define SLEEP	"is sleeping"
# define FORK	"has taken a fork"
# define EAT	"is eating"
# define THINK	"is thinking"
# define DEATH	"\033[31;1mdied\033[0m"
# define RED	"\033[31;1m"
# define GREEN	"\033[32;1m"
# define CLEAR	"\033[0m"

typedef enum e_error
{
	BAD_ARGUMENTS,
	BAD_NUMBER,
	NB_PHILO,
	THREAD_CREATE,
	MUTEX_INIT,
	MALLOC_FAIL
}		t_error;

typedef enum e_state
{
	ALIVE,
	DEAD,
	FULL
}		t_state;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FUL,
	DIE
}		t_status;

#endif
