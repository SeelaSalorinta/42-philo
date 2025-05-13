/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:09 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:12 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	divide_args(t_simulation *sim, int argc, char **argv)
{
	int	err;

	err = 0;
	sim->num_philosophers = atoi_positive_nonzero(argv[1], &err);
	if (err)
		return (1);
	sim->time_to_die = atoi_positive_nonzero(argv[2], &err);
	if (err)
		return (1);
	sim->time_to_eat = atoi_positive_nonzero(argv[3], &err);
	if (err)
		return (1);
	sim->time_to_sleep = atoi_positive_nonzero(argv[4], &err);
	if (err)
		return (1);
	if (argc == 6)
		sim->meals_required = atoi_positive_nonzero(argv[5], &err);
	else
		sim->meals_required = DEFAULT;
	return (err);
}

static int	destroy_mutexes(t_simulation *sim, int amount, int i)
{
	if (amount == 0)
		return (1);
	while (amount > 0)
	{
		if (amount == 1)
			pthread_mutex_destroy(&sim->print_lock);
		else if (amount == 2)
			pthread_mutex_destroy(&sim->eating_lock);
		else if (amount == 3)
			pthread_mutex_destroy(&sim->stop_lock);
		else if (amount == 4)
		{
			pthread_mutex_destroy(&sim->meal_time_lock);
			while (--i >= 0)
				pthread_mutex_destroy(&sim->forks[i]);
		}
		amount--;
	}
	return (1);
}

static int	init_mutexes(t_simulation *sim)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	if (pthread_mutex_init(&sim->print_lock, NULL))
		return (destroy_mutexes(sim, amount, i));
	amount++;
	if (pthread_mutex_init(&sim->eating_lock, NULL))
		return (destroy_mutexes(sim, amount, i));
	amount++;
	if (pthread_mutex_init(&sim->stop_lock, NULL))
		return (destroy_mutexes(sim, amount, i));
	amount++;
	if (pthread_mutex_init(&sim->meal_time_lock, NULL))
		return (destroy_mutexes(sim, amount, i));
	amount++;
	while (i < sim->num_philosophers)
	{
		if (pthread_mutex_init(&sim->forks[i++], NULL))
			return (destroy_mutexes(sim, amount, i));
	}
	return (0);
}

static void	init_philosophers(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].left_fork = &sim->forks[i];
		sim->philosophers[i].right_fork = &sim->forks[(i + 1)
			% sim->num_philosophers];
		sim->philosophers[i].sim = sim;
		i++;
	}
}

int	init_simulation(t_simulation *sim, int argc, char **argv)
{
	sim->philosophers = NULL;
	sim->forks = NULL;
	if (divide_args(sim, argc, argv))
		return (error_in_init(sim, ARGS_ERR));
	sim->stop_simulation = 0;
	sim->philosophers = malloc(sim->num_philosophers * sizeof(t_philosopher));
	if (!sim->philosophers)
		return (error_in_init(sim, MALLOC_ERR));
	sim->forks = malloc(sim->num_philosophers * sizeof(pthread_mutex_t));
	if (!sim->forks)
		return (error_in_init(sim, MALLOC_ERR));
	init_philosophers(sim);
	if (init_mutexes(sim))
		return (error_in_init(sim, MUTEX_ERR));
	return (0);
}
