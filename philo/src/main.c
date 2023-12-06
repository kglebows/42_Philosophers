/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/06 14:08:45 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end(t_philo *philo)
{
	int					state;

	if (ft_time(philo->dt) - philo->last_meal >= philo->dt->time_to_die)
	{
		state = pthread_mutex_unlock(&philo->lock);
		state += pthread_mutex_lock(&philo->dt->deadlock);
		philo->dt->exit = 1;
		if (state != 0)
			ft_error(-11, philo->dt);
		printf("%lld %d %s\n", ft_time(philo->dt), philo->id, DEAD);
		return (1);
	}
	state = pthread_mutex_lock(&philo->dt->happylock);
	if (philo->dt->happy_philo >= philo->dt->number_of_philosophers)
	{
		state += pthread_mutex_unlock(&philo->dt->happylock);
		state += pthread_mutex_unlock(&philo->lock);
		state += pthread_mutex_lock(&philo->dt->deadlock);
		philo->dt->exit = 1;
		if (state != 0)
			ft_error(-11, philo->dt);
		return (1);
	}
	pthread_mutex_unlock(&philo->dt->happylock);
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
		if (end(philo) == 1)
			break ;
		pthread_mutex_unlock(&philo->lock);
		philo = philo->right->right;
		usleep(1000);
	}
	ft_exit(&dt);
	return (0);
}
