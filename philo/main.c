/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:05 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:06 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				exit_num;
	t_simulation	*sim;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd(ERR_USAGE, 2);
		return (1);
	}
	sim = malloc(sizeof(t_simulation));
	if (!sim)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (1);
	}
	if (init_simulation(sim, argc, argv))
		return (1);
	exit_num = start_simulation(sim);
	cleanup_simulation(sim);
	return (exit_num);
}
