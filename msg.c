/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidgomez <aidgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:14:34 by aidgomez          #+#    #+#             */
/*   Updated: 2024/04/27 19:27:40 by aidgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	dinner_time(long init_time)
{
	long	current_time;

	current_time = get_ms_time();
	return (current_time - init_time);
}

void	print_msg(t_philo *philo, char *str, char *c1, char *c2)
{
	if (!is_end_dinner(philo->table))
	{
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%s%ld %i %s%s\n", c1, dinner_time(philo->table->init_time),
			philo->id, str, c2);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
}

void	print_death(t_philo *philo, char *str, char *c1, char *c2)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%s%ld %i %s%s\n", c1, dinner_time(philo->table->init_time),
		philo->id, str, c2);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	error_msg(char *str)
{
	printf("%sERROR!! %s%s\n", RED, str, NC);
}
