/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:17:51 by ssalorin          #+#    #+#             */
/*   Updated: 2025/04/14 13:17:55 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_found(int *error)
{
	*error = 1;
	return (1);
}

static int	skip_whitespace(char *str)
{
	int	a;

	a = 0;
	while ((str[a] && (str[a] >= 9 && str[a] <= 13))
		|| str[a] == 32)
		a++;
	return (a);
}

static long	process_digits(char *str, int *a, int *has_digit, int *error)
{
	long	nbr;

	nbr = 0;
	while (str[*a] && (str[*a] >= '0' && str[*a] <= '9'))
	{
		*has_digit = 1;
		nbr = nbr * 10 + (str[*a] - '0');
		if (nbr > INT_MAX)
			return (error_found(error));
		(*a)++;
	}
	if (str[*a] != '\0')
		return (error_found(error));
	return (nbr);
}

int	atoi_positive_nonzero(char *str, int *error)
{
	int		a;
	int		has_digit;
	long	nbr;
	int		sign;

	has_digit = 0;
	nbr = 0;
	sign = 1;
	a = skip_whitespace(str);
	if (str[a] && (str[a] == '-' || str[a] == '+'))
	{
		if (str[a] == '-')
			return (error_found(error));
		a++;
	}
	nbr = process_digits(str, &a, &has_digit, error);
	if (!has_digit || *error)
		return (error_found(error));
	if (nbr == 0)
		return (error_found(error));
	return (sign * nbr);
}
