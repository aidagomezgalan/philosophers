/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidgomez <aidgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:20:03 by aidgomez          #+#    #+#             */
/*   Updated: 2024/04/26 15:50:58 by aidgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo	*philo)
{
	long	end_routine;

	picking_forks(philo);
	if (philo->table->philos_nbr == 1)
	{
		end_routine = get_ms_time() + philo->table->death_time;
		while (get_ms_time() <= end_routine)
			;
		philo_death(philo->table, philo);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		set_last_meal(philo);
		print_msg(philo, "is eating", GREEN, NC);
		time_counter(philo->table->eat_time, philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		set_nbr_meals(philo);
	}
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping", BLUE, NC);
	time_counter(philo->table->sleep_time, philo);
}

void	thinking(t_philo *philo)
{
	print_msg(philo, "is thinking", PURPLE, NC);
}

void	*thread_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!is_end_dinner(philo->table))
	{
		eating(philo);
		if (!is_end_dinner(philo->table))
			sleeping(philo);
		if (!is_end_dinner(philo->table))
			thinking(philo);
	}
	return (NULL);
}
