/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:18:55 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/16 14:58:25 by atasyure         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, int flag)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (flag)
		print_curr(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*only_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime_ms());
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	print_curr(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->first_fork->fork))
		return ;
	print_curr(TAKE_FIRST_FORK, philo);
	if (pthread_mutex_lock(&philo->second_fork->fork))
		return ;
	print_curr(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime_ms());
	philo->meals_counter++;
	print_curr(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_int(&philo->philo_mutex, &philo->full, TRUE);
	if (pthread_mutex_unlock(&philo->first_fork->fork))
		return ;
	if (pthread_mutex_unlock(&philo->second_fork->fork))
		return ;
}

void	*dinner(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime_ms());
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	desynch(philo);
	while (!simulation_finished(philo->table))
	{
		if (get_int(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		print_curr(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		think(philo, TRUE);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int			i;

	i = -1;
	if (table->philo_nbr == 1)
	{
		if (pthread_create(&table->philos[0].thread_id, NULL,
				only_philo, &table->philos[0]))
			return ;
	}
	else
		while (++i < table->philo_nbr)
			if (pthread_create(&table->philos[i].thread_id,
					NULL, dinner, &table->philos[i]))
				return ;
	if (pthread_create(&table->monitor, NULL, monitor_dinner, table))
		return ;
	table->start_simulation = gettime_ms();
	set_int(&table->table_mutex, &table->all_threads_ready, TRUE);
	i = -1;
	while (++i < table->philo_nbr)
		if (pthread_join(table->philos[i].thread_id, NULL))
			return ;
	set_int(&table->table_mutex, &table->end_simulation, TRUE);
	if (pthread_join(table->monitor, NULL))
		return ;
}
