/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:20:04 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/11 00:20:05 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	long	elapsed;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (FALSE);
	elapsed = gettime_ms() - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	if (elapsed > philo->table->time_to_die)
		return (TRUE);
	return (FALSE);
}

void	*monitor_dinner(void *data)
{
	int			i;
	t_table		*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_nbr, table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_int(&table->table_mutex, &table->end_simulation, TRUE);
				print_curr(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}

void	wait_all_threads(t_table *table)
{
	while (!get_int(&table->table_mutex, &table->all_threads_ready))
		;
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	if (pthread_mutex_lock(mutex))
		return ;
	(*value)++;
	if (pthread_mutex_unlock(mutex))
		return ;
}

int	all_threads_running(pthread_mutex_t *mutex, long *threads,
		long philo_nbr)
{
	int	ret;

	ret = FALSE;
	if (pthread_mutex_lock(mutex))
		return (FAILURE);
	if (*threads == philo_nbr)
		ret = TRUE;
	if (pthread_mutex_unlock(mutex))
		return (FAILURE);
	return (ret);
}
