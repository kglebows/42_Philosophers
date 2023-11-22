/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/22 16:08:31 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_counter(t_philo *philo)
{
	int				i;

	pthread_mutex_lock(&philo->lock);
	i = philo->dt->number_of_times_each_philosopher_must_eat;
	if (i > 0 && philo->happy == 0)
	{
		if (philo->meals_had >= i)
		{
			philo->dt->happy_philo++;
			philo->happy = 1;
		}
	}
	pthread_mutex_unlock(&philo->lock);
	if (i == 0 || philo->dt->happy_philo == philo->dt->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->dt->deadlock);
		philo->dt->exit = 1;
		return (1);
	}
	return (0);
}

int	main(int argn, char *argc[])
{
	t_dt				dt;
	t_philo				*philo;
	int					state;

	ft_ini(argn, argc, &dt);
	philo = dt.philo;
	while (1)
	{
		state = pthread_mutex_lock(&philo->lock);
		if (ft_time(&dt) - philo->last_meal >= dt.time_to_die)
		{
			state += pthread_mutex_unlock(&philo->lock);
			state += pthread_mutex_lock(&dt.deadlock);
			dt.exit = 1;
			printf("%lld %d %s\n", ft_time(philo->dt), philo->id, DEAD);
			break ;
		}
		state = pthread_mutex_unlock(&philo->lock);
		if (meal_counter(philo) == 1)
			break ;
		usleep(1000);
	}
	ft_exit(&dt);
	return (0);
}
