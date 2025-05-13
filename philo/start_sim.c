/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:48 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:49 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_threads(t_simulation *sim, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_lock(&sim->meal_time_lock);
		sim->philosophers[i].last_meal_time = sim->start_time;
		pthread_mutex_unlock(&sim->meal_time_lock);
		if (pthread_create(&threads[i], NULL, philosopher_routine,
				&sim->philosophers[i]))
		{
			ft_putstr_fd(ERR_THREAD_CREATION, 2);
			while (--i >= 0)
			{
				if (pthread_join(threads[i], NULL))
				{
					ft_putstr_fd(ERR_THREAD_JOIN, 2);
					return (1);
				}
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_threads(t_simulation *sim, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		if (pthread_join(threads[i++], NULL))
		{
			ft_putstr_fd(ERR_THREAD_JOIN, 2);
			return ;
		}
	}
}

int	start_simulation(t_simulation *sim)
{
	pthread_t	*threads;
	pthread_t	monitor;

	threads = malloc(sim->num_philosophers * sizeof(pthread_t));
	if (!threads)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (1);
	}
	sim->start_time = current_time();
	if (init_threads(sim, threads))
	{
		free(threads);
		return (1);
	}
	if (pthread_create(&monitor, NULL, monitor_death, sim))
		return (thread_err(CREATE_ERR, sim, threads));
	if (pthread_join(monitor, NULL))
		return (thread_err(JOIN_ERR, sim, threads));
	join_threads(sim, threads);
	free(threads);
	return (0);
}
