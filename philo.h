/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidgomez <aidgomez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 14:07:02 by aidgomez          #+#    #+#             */
/*   Updated: 2024/04/30 12:39:39 by aidgomez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

# define NC "\e[0m"
# define YELLOW "\e[1;33m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;34m"

// # define malloc(...) NULL

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			meals_count;
	long		last_meal;
	t_table		*table;
	t_mutex		*r_fork;
	t_mutex		*l_fork;
	pthread_t	tid;
}				t_philo;

typedef struct s_table
{
	int			meals_nbr;
	int			philos_nbr;
	int			end_dinner;
	int			total_meals;
	long		death_time;
	long		eat_time;
	long		sleep_time;
	long		init_time;
	t_philo		*a_philos;
	t_mutex		*a_forks;
	t_mutex		meals_lock;
	t_mutex		print_lock;
	t_mutex		end;
}				t_table;

// data_checker.c
int		data_checker(int argc, char **argv);
long	ft_atol(char *str);

// struct_init.c
long	get_ms_time(void);
t_table	table_init(char **argv);
int		forks_init(t_table	*table);
int		philos_init(t_table	*table);

// utils.c
void	safe_mutex_init(t_mutex *mutex);
void	safe_thread_create(t_table *t, int i, void *(*ini)(void *));
void	memory_mutex_free(t_table *table);

// msg.c
long	dinner_time(long init_time);
void	print_msg(t_philo *philo, char *str, char *c1, char *c2);
void	print_death(t_philo *philo, char *str, char *c1, char *c2);
void	error_msg(char *str);

// threads_routine.c
void	*thread_routine(void *data);

// threads_utils.c
void	time_counter(long time, t_philo *philo);
void	set_nbr_meals(t_philo *philo);
void	picking_forks(t_philo *philo);
void	set_last_meal(t_philo *philo);

// monitor.c
void	philo_death(t_table *table, t_philo *philo);
void	check_meals(t_table *table);
int		is_end_dinner(t_table *table);
void	check_death_time(t_table *table);

// main.c
int		main(int argc, char **argv);

#endif
