/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42kocaeli.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 23:56:07 by atasyure          #+#    #+#             */
/*   Updated: 2024/01/11 00:10:27 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	digit_control(char **argv)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (argv[i])
	{
		while (argv[i][c])
		{
			if (argv[i][c] < '0' || argv[i][c] > '9')
				return (FAILURE);
			c++;
		}
		c = 0;
		i++;
	}
	return (SUCCESS);
}

long	ft_atol(const char *str)
{
	int		sign;
	int		i;
	long	result;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	input_value(int argc, char **argv)
{
	if (ft_atol(argv[1]) < 1)
		return (FAILURE);
	if (argc == 6 && ft_atol(argv[5]) < 1)
		return (FAILURE);
	return (SUCCESS);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (FAILURE);
	if (digit_control(argv + 1))
		return (FAILURE);
	if (input_value(argc, argv))
		return (FAILURE);
	return (SUCCESS);
}

void	format_error(void)
{
	printf("Usage limited to integer characters:\n");
	printf("./philo number_of_philosophers time_to_die ");
	printf("time_to_eat time_to_sleep ");
	printf("necessary_number_of_meals(optional)\n");
	printf("Philosopher number has to be greater than zero\n");
	printf("The meal number must be greater than zero when entered.\n");
}
