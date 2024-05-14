/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidgomez <aidgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:29:21 by aidgomez          #+#    #+#             */
/*   Updated: 2024/04/25 10:30:51 by aidgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	nbr;
	int		len;

	nbr = 0;
	len = 0;
	if (*str == '\0')
		return (0);
	while (*str == ' ' || *str == '\n' || *str == '\f'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
		return (0);
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
		len++;
	}
	if (len > 10)
		return (0);
	return (nbr);
}

int	is_nbr(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_nbr(char *str)
{
	long	nbr;

	nbr = ft_atol(str);
	if (nbr < 0)
		return (0);
	if (nbr > INT_MAX)
		return (0);
	return (1);
}

int	data_checker(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	if (ft_atol(argv[1]) == 0)
		return (0);
	while (i < argc)
	{
		if (!is_nbr(argv[i]))
			return (0);
		if (!is_valid_nbr(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
