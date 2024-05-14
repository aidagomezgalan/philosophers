/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidgomez <aidgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:23:55 by aidgomez          #+#    #+#             */
/*   Updated: 2024/04/26 16:06:11 by aidgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_mutex_init(t_mutex *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		error_msg("Mutex no ha sido iniciado");
}

void	safe_thread_create(t_table *t, int i, void *(*ini)(void *))
{
	if (pthread_create(&t->a_philos[i].tid, NULL,
			ini, &t->a_philos[i]) != 0)
		error_msg("Hilo no ha sido creado");
}

void	mutex_free(t_mutex *mutex, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_mutex_destroy(mutex);
		i++;
	}
}

void	memory_mutex_free(t_table *table)
{
	pthread_mutex_destroy(&table->end);
	pthread_mutex_destroy(&table->meals_lock);
	pthread_mutex_destroy(&table->print_lock);
	mutex_free(table->a_forks, table);
	pthread_mutex_destroy(table->a_philos->r_fork);
	if (table->a_philos->l_fork)
		pthread_mutex_destroy(table->a_philos->l_fork);
	free(table->a_forks);
	free(table->a_philos);
}
