/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:23 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:24 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	int					stop_simulation;
	long long			last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_simulation	*sim;
}	t_philosopher;

typedef struct s_simulation
{
	int				num_philosophers;
	int				meals_required;
	int				stop_simulation;
	int				all_eaten_enough;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	meal_time_lock;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
}	t_simulation;

typedef enum e_flag
{
	MUTEX_ERR,
	CREATE_ERR,
	JOIN_ERR,
	MALLOC_ERR,
	ARGS_ERR,
	DEFAULT = -2,
}	t_flag;

//init_sim.c
int			init_simulation(t_simulation *sim, int argc, char **argv);

//start_sim.c
int			start_simulation(t_simulation *sim);
void		join_threads(t_simulation *sim, pthread_t *threads);

//philo_actions.c
void		print_status(t_philosopher *philo, char *status);
void		eat(t_philosopher *philo);
long long	current_time(void);
void		philo_sleep(long long time, t_philosopher *philo);
void		ft_putstr_fd(char *s, int fd);

//monitor_sim.c
int			all_eaten_enough(t_simulation *sim);
int			has_died(t_philosopher *philo);
int			check_stop(t_philosopher *philo);
void		*monitor_death(void *arg);

//philo_routine.c
void		*philosopher_routine(void *arg);

//cleanup_and_error.c
void		cleanup_simulation(t_simulation *sim);
int			thread_err(int err, t_simulation *sim, pthread_t *threads);
int			error_in_init(t_simulation *sim, int err);

//atoi.c
int			atoi_positive_nonzero(char *str, int *error);

# define STATUS_THINKING "is thinking"
# define STATUS_EATING "is eating"
# define STATUS_SLEEPING "is sleeping"
# define STATUS_FORK "has taken a fork"
# define STATUS_DIED "died"
# define ERR_THREAD_CREATION "Error: Failed to create thread\n"
# define ERR_THREAD_JOIN "Error: Failed to join thread\n"
# define ERR_MUTEX_INIT "Error: Failed to initialize mutex\n"
# define ERR_MUTEX_DESTROY "Error: Failed to destroy mutex\n"
# define ERR_MALLOC "Error: Memory allocation failed\n"
# define ERR_ARGS "Error: Invalid argumets\n"
# define ERR_USAGE "Usage: ./philo num_philos time_to_die time_to_eat \
time_to_sleep [meals_required]\n"

#endif
