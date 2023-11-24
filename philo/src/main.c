/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/24 15:43:13 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_counter(t_philo *philo)
{
	int				i;

	i = philo->dt->number_of_times_each_philosopher_must_eat;
	if (i > 0 && philo->happy == 0)
	{
		if (philo->meals_had >= i)
		{
			philo->dt->happy_philo++;
			philo->happy = 1;
		}
	}
}

int	end(t_philo *philo)
{
	int					state;

	state = 0;
	if (ft_time(philo->dt) - philo->last_meal >= philo->dt->time_to_die)
	{
		state += pthread_mutex_unlock(&philo->lock);
		state += pthread_mutex_lock(&philo->dt->deadlock);
		philo->dt->exit = 1;
		if (state != 0)
			ft_error(-11, philo->dt);
		printf("%lld %d %s\n", ft_time(philo->dt), philo->id, DEAD);
		return (1);
	}
	if (philo->dt->happy_philo >= philo->dt->number_of_philosophers)
	{
		state += pthread_mutex_unlock(&philo->lock);
		state += pthread_mutex_lock(&philo->dt->deadlock);
		philo->dt->exit = 1;
		if (state != 0)
			ft_error(-11, philo->dt);
		return (1);
	}
	return (0);
}

int	main(int argn, char *argc[])
{
	t_dt				dt;
	t_philo				*philo;

	ft_ini(argn, argc, &dt);
	philo = dt.philo;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		meal_counter(philo);
		if (end(philo) == 1)
			break ;
		pthread_mutex_unlock(&philo->lock);
		philo = philo->right->right;
		usleep(1000);
	}
	ft_exit(&dt);
	return (0);
}
