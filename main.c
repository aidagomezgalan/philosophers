/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidgomez <aidgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:50:57 by aidgomez          #+#    #+#             */
/*   Updated: 2024/04/27 19:26:51 by aidgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threads_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		safe_thread_create(table, i, thread_routine);
		i++;
	}
}

void	threads_end(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_nbr)
	{
		pthread_join(table->a_philos[i].tid, NULL);
		i++;
	}
}

int	start_dinner(char **argv)
{
	t_table	table;

	table = table_init(argv);
	if (!forks_init(&table) || !philos_init(&table))
		return (0);
	threads_init(&table);
	while (!is_end_dinner(&table) && table.philos_nbr > 1)
	{
		check_death_time(&table);
		if (table.meals_nbr > 0)
			check_meals(&table);
	}
	threads_end(&table);
	if (table.meals_nbr >= 0 && table.philos_nbr == table.total_meals)
		printf("%sEveryone has eaten %i times%s\n", GREEN, table.meals_nbr, NC);
	printf("THE DINNER IS OVER!!!!!\n");
	memory_mutex_free(&table);
	return (1);
}

int	main(int argc, char **argv)
{
	if (!data_checker(argc, argv))
		printf("%sERROR!!\nAlmost 4 int positive params%s\n", RED, NC);
	else if (!start_dinner(argv))
		error_msg("Falló Malloc");
	return (0);
}
