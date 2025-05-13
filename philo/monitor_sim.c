/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:16 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:17 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten_enough(t_simulation *sim)
{
	int	i;

	if (sim->meals_required == DEFAULT)
		return (0);
	i = 0;
	pthread_mutex_lock(&sim->eating_lock);
	while (i < sim->num_philosophers)
	{
		if (sim->philosophers[i].meals_eaten
			< sim->meals_required)
		{
			pthread_mutex_unlock(&sim->eating_lock);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&sim->eating_lock);
	pthread_mutex_lock(&sim->stop_lock);
	sim->stop_simulation = 1;
	pthread_mutex_unlock(&sim->stop_lock);
	return (1);
}

int	has_died(t_philosopher *philo)
{
	long long	time_since_last_meal;
	long long	now;

	now = current_time();
	pthread_mutex_lock(&philo->sim->meal_time_lock);
	time_since_last_meal = now - philo->last_meal_time;
	pthread_mutex_unlock(&philo->sim->meal_time_lock);
	if (time_since_last_meal > philo->sim->time_to_die)
	{
		pthread_mutex_lock(&philo->sim->stop_lock);
		if (!philo->sim->stop_simulation)
		{
			philo->sim->stop_simulation = 1;
			pthread_mutex_unlock(&philo->sim->stop_lock);
			pthread_mutex_lock(&philo->sim->print_lock);
			printf("%lld %d %s\n", now - philo->sim->start_time,
				philo->id, STATUS_DIED);
			pthread_mutex_unlock(&philo->sim->print_lock);
			return (1);
		}
		else
			pthread_mutex_unlock(&philo->sim->stop_lock);
		return (1);
	}
	return (0);
}

int	check_stop(t_philosopher *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->sim->stop_lock);
	stop = philo->sim->stop_simulation;
	pthread_mutex_unlock(&philo->sim->stop_lock);
	return (stop);
}

int	someone_died(t_simulation *sim)
{
	int		i;

	i = 0;
	if (check_stop(&sim->philosophers[0]))
		return (1);
	while (i < sim->num_philosophers)
	{
		if (has_died(&sim->philosophers[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (1)
	{
		if (all_eaten_enough(sim) || someone_died(sim))
			break ;
		usleep(100);
	}
	return (NULL);
}
