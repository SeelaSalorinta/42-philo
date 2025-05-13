/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:17:59 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:01 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		if (pthread_mutex_destroy(&sim->forks[i]) != 0)
			ft_putstr_fd(ERR_MUTEX_DESTROY, 2);
		i++;
	}
	if (pthread_mutex_destroy(&sim->print_lock) != 0)
		ft_putstr_fd(ERR_MUTEX_DESTROY, 2);
	if (pthread_mutex_destroy(&sim->eating_lock) != 0)
		ft_putstr_fd(ERR_MUTEX_DESTROY, 2);
	if (pthread_mutex_destroy(&sim->stop_lock) != 0)
		ft_putstr_fd(ERR_MUTEX_DESTROY, 2);
	if (pthread_mutex_destroy(&sim->meal_time_lock) != 0)
		ft_putstr_fd(ERR_MUTEX_DESTROY, 2);
}

void	cleanup_simulation(t_simulation *sim)
{
	cleanup_mutexes(sim);
	if (sim->philosophers)
		free(sim->philosophers);
	if (sim->forks)
		free(sim->forks);
	free(sim);
}

int	thread_err(int err, t_simulation *sim, pthread_t *threads)
{
	pthread_mutex_lock(&sim->stop_lock);
	sim->stop_simulation = 1;
	pthread_mutex_unlock(&sim->stop_lock);
	if (err == CREATE_ERR)
		ft_putstr_fd(ERR_THREAD_CREATION, 2);
	else if (err == JOIN_ERR)
		ft_putstr_fd(ERR_THREAD_JOIN, 2);
	join_threads(sim, threads);
	free(threads);
	return (1);
}

int	error_in_init(t_simulation *sim, int err)
{
	if (err == ARGS_ERR)
		ft_putstr_fd(ERR_ARGS, 2);
	else if (err == MALLOC_ERR)
		ft_putstr_fd(ERR_MALLOC, 2);
	else if (err == MUTEX_ERR)
		ft_putstr_fd(ERR_MUTEX_INIT, 2);
	if (sim->philosophers)
		free(sim->philosophers);
	if (sim->forks)
		free(sim->forks);
	free(sim);
	return (1);
}
