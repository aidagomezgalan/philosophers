/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidgomez <aidgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:19:24 by aidgomez          #+#    #+#             */
/*   Updated: 2024/04/26 15:45:17 by aidgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_nbr_meals(t_philo *philo)
{
	if (philo->table->meals_nbr > 0)
		philo->meals_count++;
	if (philo->meals_count == philo->table->meals_nbr)
	{
		pthread_mutex_lock(&philo->table->meals_lock);
		philo->table->total_meals += 1;
		pthread_mutex_unlock(&philo->table->meals_lock);
	}
}

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meals_lock);
	philo->last_meal = get_ms_time();
	pthread_mutex_unlock(&philo->table->meals_lock);
}

void	time_counter(long time, t_philo *philo)
{
	long	end_routine;

	end_routine = get_ms_time() + time;
	while (get_ms_time() < end_routine)
		if (is_end_dinner(philo->table))
			return ;
}

void	pick_fork(t_philo *philo, t_mutex *fork)
{
	if (fork)
	{
		pthread_mutex_lock(fork);
		print_msg(philo, "has taken a fork", YELLOW, NC);
	}
}

void	picking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pick_fork(philo, philo->r_fork);
		pick_fork(philo, philo->l_fork);
	}
	else
	{
		pick_fork(philo, philo->l_fork);
		pick_fork(philo, philo->r_fork);
	}
}
