/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:49:50 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/16 14:34:31 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> 
# include <stdlib.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE -1

typedef enum e_curr
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_curr;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

typedef struct s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				philo_nbr;
	long				start_simulation;
	int					end_simulation;
	int					all_threads_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_fork				*forks;
	struct s_philo		*philos;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
}				t_table;

typedef struct s_philo
{
	int				id;
	int				full;
	long			meals_counter;
	long			last_meal_time;
	pthread_t		thread_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}				t_philo;

int		data_init(t_table *table);
int		philo_died(t_philo *philo);
int		get_int(pthread_mutex_t *mutex, int *value);
int		simulation_finished(t_table *table);
int		digit_control(char **argv);
int		input_value(int argc, char **argv);
int		check_input(int argc, char **argv);
int		all_threads_running(pthread_mutex_t *mutex, long *threads,
			long philo_nbr);

long	get_long(pthread_mutex_t *mutex, long *value);
long	gettime_ms(void);
long	gettime_microsec(void);
long	ft_atol(const char *str);

void	assign_forks(t_philo *philo, t_fork *forks, int philo_iposition);
void	philo_init(t_table *table);
void	eat(t_philo *philo);
void	think(t_philo *philo, int flag);
void	*dinner(void *data);
void	*only_philo(void *arg);
void	dinner_start(t_table *table);
void	format_input(t_table *table, char **argv);
void	*monitor_dinner(void *data);
void	wait_all_threads(t_table *table);
void	increase_long(pthread_mutex_t *mutex, long *value);
void	set_int(pthread_mutex_t *mutex, int *dest, int value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
void	print_curr(t_philo_curr status, t_philo *philo);
void	format_error(void);
void	precise_usleep(long usec, t_table *table);
void	desynch(t_philo *philo);
void	clean(t_table *table);

#endif
