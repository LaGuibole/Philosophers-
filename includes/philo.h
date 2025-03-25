/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:30:21 by guphilip          #+#    #+#             */
/*   Updated: 2025/03/25 14:39:14 by guphilip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// COLORS

# define RED "\033[31m"
# define BLUE "\033[34m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

// LIBS

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>

// DEFINES

# define ARG1 				"number of philosophers"
# define ARG2 				"time_to_die"
# define ARG3 				"time_to_eat"
# define ARG4 				"time_to_sleep"
# define ARG5 				"number_of_times_philosophers_must_eat"
# define ERR_NAT_INT		"must be a natural integer"

# define ERR_NULL			"cannot be null"
# define ERR_MUTEX			"mutex initialization error"
# define ERR_ALLOC			"Bad allocation"
# define ERR_THREAD_INIT	"Thread initialization error"

# define RET_OK 0
# define RET_ERR 1

// MESSAGES

// ENUMS

typedef enum e_args
{
	PROG_NAME,
	PROG_PHILO_COUNT,
	PROG_DEATH_TIMER,
	PROG_EAT_TIMER,
	PROG_SLEEP_TIMER,
	PROG_EACHP_TIMER,
	PROG__MIN=PROG_SLEEP_TIMER + 1,
	PROG__MAX=PROG_EACHP_TIMER + 1,
}			t_args;

typedef enum e_state
{
	STATE_FORK_TAKEN,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_THINKING,
	STATE_DIED,
}			t_state;

// STRUCTURES

typedef struct	s_philo
{
	pthread_t		thread_id;
	int				id;
	bool			is_dead;
	unsigned int	times_eaten;
	time_t			last_time_eaten;
	pthread_mutex_t	mutex_eating;
	pthread_mutex_t mutex_eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *r_fork;
	void			*ctx;
}				t_philo;

typedef struct s_philo_ctx
{
	char			*program_name;
	unsigned int	philo_count;
	bool			is_running;
	pthread_mutex_t mutex_is_running;
	struct	s_timers
	{
		time_t death;
		time_t eat;
		time_t sleep;
		unsigned int each;
	}		timers;
	t_philo			*philos;
	pthread_mutex_t *forks;
}				t_philo_ctx;


// FONCTIONS


#endif
