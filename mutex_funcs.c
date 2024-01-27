/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:21:47 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/11 00:21:48 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(pthread_mutex_t	*mutex, int *dest, int value)
{
	if (pthread_mutex_lock(mutex))
		return ;
	*dest = value;
	if (pthread_mutex_unlock(mutex))
		return ;
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	if (pthread_mutex_lock(mutex))
		return ;
	*dest = value;
	if (pthread_mutex_unlock(mutex))
		return ;
}

int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	ret;

	if (pthread_mutex_lock(mutex))
		return (FAILURE);
	ret = *value;
	if (pthread_mutex_unlock(mutex))
		return (FAILURE);
	return (ret);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	if (pthread_mutex_lock(mutex))
		return (FAILURE);
	ret = *value;
	if (pthread_mutex_unlock(mutex))
		return (FAILURE);
	return (ret);
}

int	simulation_finished(t_table *table)
{
	return (get_int(&table->table_mutex, &table->end_simulation));
}
