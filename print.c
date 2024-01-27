/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:22:17 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/15 17:00:48 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_curr(t_philo_curr status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime_ms() - philo->table->start_simulation;
	if (get_int(&philo->philo_mutex, &philo->full))
		return ;
	if (pthread_mutex_lock(&philo->table->write_mutex))
		return ;
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& !simulation_finished(philo->table))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf("%ld %d died\n", elapsed, philo->id);
	if (pthread_mutex_unlock(&philo->table->write_mutex))
		return ;
}
