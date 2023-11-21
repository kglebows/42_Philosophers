/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:42:58 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/21 16:01:26 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	isnum(const char *str)
{
	while (*str != '\0')
	{
		if (!(ft_isdigit((int) *str)))
			return (0);
		str++;
	}
	return (1);
}

long	ft_atoi(const char *str, t_dt *dt)
{
	long		n;
	int			s;

	s = 1;
	n = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	if (!isnum(str) || n * s > 2147483647 || n * s < 0)
		ft_error(-3, dt);
	return (n * s);
}

void	ft_ini_arguments(int argn, char *argc[], t_dt *dt)
{
	dt->number_of_philosophers = ft_atoi(argc[1], dt);
	dt->time_to_die = ft_atoi(argc[2], dt);
	dt->time_to_eat = ft_atoi(argc[3], dt);
	dt->time_to_sleep = ft_atoi(argc[4], dt);
	dt->exit = 0;
	dt->happy_philo = 0;
	dt->start_time = 0;
	if (argn == 6)
		dt->number_of_times_each_philosopher_must_eat = ft_atoi(argc[5], dt);
	else
		dt->number_of_times_each_philosopher_must_eat = -1;
}
