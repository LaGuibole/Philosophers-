/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guphilip <guphilip@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:30:21 by guphilip          #+#    #+#             */
/*   Updated: 2025/04/01 18:45:30 by guphilip         ###   ########.fr       */
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

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>

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

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	bool			is_dead;
	unsigned int	times_eaten;
	long long		last_time_eaten;
	pthread_mutex_t	mutex_eating;
	pthread_mutex_t	mutex_eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	void			*ctx;
}				t_philo;

typedef struct s_philo_ctx
{
	char			*program_name;
	unsigned int	philo_count;
	bool			is_running;
	bool			someone_died;
	long long		start_time;
	pthread_mutex_t	mutex_is_running;
	pthread_mutex_t	mutex_someone_died;
	pthread_mutex_t	mutex_print;
	struct	s_timers
	{
		time_t			death;
		time_t			eat;
		time_t			sleep;
		unsigned int	each;
	}		timers;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}				t_philo_ctx;

// FONCTIONS
int			print_error(char *msg);
int			init_context(t_philo_ctx *ctx);
int			init_forks(t_philo_ctx *ctx);
int			init_philosophers(t_philo_ctx *ctx);
int			create_monitor_thread(t_philo_ctx *ctx);
int			init_threads(t_philo_ctx *ctx);
int			init_simulation(t_philo_ctx *ctx);
void		clean_philo_mutex_error(t_philo_ctx *ctx, unsigned int i);
void		clean_forks_error(t_philo_ctx *ctx, unsigned int i);
void		clean_forks(t_philo_ctx *ctx);
void		handle_thread_error(t_philo_ctx *ctx, unsigned int i);
void		clean_philosophers(t_philo_ctx *ctx);
void		clean_context(t_philo_ctx *ctx);
int			is_digit(int n);
long		ft_atol(char *str);
int			parse_value(char *arg, long *dest, char *err_msg);
int			parse_args(int argc, char **argv, t_philo_ctx *ctx);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo, t_philo_ctx *ctx);
void		release_forks(t_philo *philo);
void		think(t_philo *philo);
void		sleep_philosophers(t_philo *philo);
bool		check_philosopher_death(t_philo *philo);
void		signal_death(t_philo *philo, t_philo_ctx *ctx);
bool		check_all_eaten(t_philo_ctx *ctx);
void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);
long long	get_current_time(void);
void		custom_sleep(long long ms);
void		print_status(t_philo *philo, t_state state);
void		set_running(t_philo_ctx *ctx, bool state);
bool		is_running(t_philo_ctx *ctx);

#endif
