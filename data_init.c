/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:19:16 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/11 00:19:57 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_philo *philo, t_fork *forks,
		int philo_iposition)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_iposition + 1) % philo_nbr];
	philo->second_fork = &forks[philo_iposition];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_iposition];
		philo->second_fork = &forks[(philo_iposition + 1) % philo_nbr];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = FALSE;
		philo->meals_counter = 0;
		if (pthread_mutex_init(&philo->philo_mutex, NULL))
			return ;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

int	data_init(t_table *table)
{
	int		i;

	i = -1;
	table->end_simulation = FALSE;
	table->all_threads_ready = FALSE;
	table->threads_running_nbr = FALSE;
	table->philos = malloc(table->philo_nbr * sizeof(t_philo));
	table->forks = malloc(table->philo_nbr * sizeof(t_fork));
	if (!table->forks || !table->philos)
		return (FAILURE);
	if (pthread_mutex_init(&table->write_mutex, NULL))
		return (FAILURE);
	if (pthread_mutex_init(&table->table_mutex, NULL))
		return (FAILURE);
	while (++i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL))
			return (FAILURE);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	return (SUCCESS);
}
