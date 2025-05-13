/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:41 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:43 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, STATUS_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, STATUS_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, STATUS_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, STATUS_FORK);
	}
}

static long long	get_last_meal(t_philosopher *philo)
{
	long long		last;

	pthread_mutex_lock(&philo->sim->meal_time_lock);
	last = philo->last_meal_time;
	pthread_mutex_unlock(&philo->sim->meal_time_lock);
	return (last);
}

static int	should_wait(t_philosopher *philo)
{
	t_philosopher	*left;
	t_philosopher	*right;
	long long		my_time;
	long long		left_time;
	long long		right_time;

	left = &philo->sim->philosophers[(philo->id - 2
			+ philo->sim->num_philosophers) % philo->sim->num_philosophers];
	right = &philo->sim->philosophers[philo->id % philo->sim->num_philosophers];
	my_time = get_last_meal(philo);
	left_time = get_last_meal(left);
	right_time = get_last_meal(right);
	if (check_stop(philo))
		return (0);
	if (my_time > left_time || my_time > right_time)
		return (1);
	return (0);
}

static void	philosopher_loop(t_philosopher *philo)
{
	while (!check_stop(philo))
	{
		print_status(philo, STATUS_THINKING);
		while (should_wait(philo))
			usleep(100);
		take_forks(philo);
		eat(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (check_stop(philo))
			break ;
		print_status(philo, STATUS_SLEEPING);
		philo_sleep(philo->sim->time_to_sleep, philo);
		usleep(100);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	if (philo->sim->num_philosophers == 1)
	{
		print_status(philo, STATUS_THINKING);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, STATUS_FORK);
		philo_sleep(philo->sim->time_to_die, philo);
		has_died(philo);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	philosopher_loop(philo);
	return (NULL);
}
