/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidgomez <aidgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:15:47 by aidgomez          #+#    #+#             */
/*   Updated: 2024/04/26 11:42:43 by aidgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_death(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->end);
	table->end_dinner = 1;
	pthread_mutex_unlock(&table->end);
	print_death(philo, "died", RED, NC);
}

void	check_meals(t_table *table)
{
	pthread_mutex_lock(&table->meals_lock);
	if (table->total_meals == table->philos_nbr || table->meals_nbr == 0)
	{
		pthread_mutex_unlock(&table->meals_lock);
		pthread_mutex_lock(&table->end);
		table->end_dinner = 1;
		pthread_mutex_unlock(&table->end);
	}
	else
		pthread_mutex_unlock(&table->meals_lock);
}

void	check_death_time(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_mutex_lock(&table->meals_lock);
		if ((get_ms_time() - table->a_philos[i].last_meal) > table->death_time)
		{
			pthread_mutex_unlock(&table->meals_lock);
			philo_death(table, &table->a_philos[i]);
			return ;
		}
		pthread_mutex_unlock(&table->meals_lock);
		i++;
	}
}

int	is_end_dinner(t_table *table)
{
	pthread_mutex_lock(&table->end);
	if (table->end_dinner == 0)
	{
		pthread_mutex_unlock(&table->end);
		return (0);
	}
	pthread_mutex_unlock(&table->end);
	return (1);
}
