/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:21:00 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/16 15:02:23 by atasyure         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long	gettime_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (FAILURE);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	gettime_microsec(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (FAILURE);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime_microsec();
	while (gettime_microsec() - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime_microsec() - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
			while (gettime_microsec() - start < usec)
				;
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}

void	desynch(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3000, philo->table);
	}
	else
	{
		if (philo->id % 2)
			think(philo, FALSE);
	}
}
