/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:31 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:33 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_status(t_philosopher *philo, char *status)
{
	if (!check_stop(philo))
	{
		pthread_mutex_lock(&philo->sim->print_lock);
		printf("%lld %d %s\n", current_time() - philo->sim->start_time,
			philo->id, status);
		pthread_mutex_unlock(&philo->sim->print_lock);
	}
}

void	eat(t_philosopher *philo)
{
	if (check_stop(philo))
		return ;
	pthread_mutex_lock(&philo->sim->meal_time_lock);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(&philo->sim->meal_time_lock);
	print_status(philo, STATUS_EATING);
	philo_sleep(philo->sim->time_to_eat, philo);
	pthread_mutex_lock(&philo->sim->eating_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->sim->eating_lock);
}

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_sleep(long long time, t_philosopher *philo)
{
	long long	start;

	start = current_time();
	while (current_time() - start < time)
	{
		if (check_stop(philo))
			break ;
		usleep(100);
	}
}
