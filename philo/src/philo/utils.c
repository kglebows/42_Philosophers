/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:17:23 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/22 16:45:30 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(t_dt *dt)
{
	int					state;
	struct timeval		now;
	long long			time;

	state = pthread_mutex_lock(&dt->timelock);
	state += gettimeofday(&now, NULL);
	time = now.tv_sec * 1000L + now.tv_usec / 1000L - dt->start_time;
	state += pthread_mutex_unlock(&dt->timelock);
	if (state != 0)
		ft_error(-5, dt);
	return (time);
}

long long	ft_say(char *str, t_philo *philo)
{
	long long		time;
	int				state;

	state = pthread_mutex_lock(&philo->dt->deadlock);
	if (philo->dt->exit != 0)
	{
		state += pthread_mutex_unlock(&philo->dt->deadlock);
		return (0);
	}
	time = ft_time(philo->dt);
	if (philo->dt->exit == 0)
		printf("%lld %d %s\n", time, philo->id, str);
	if (ft_strncmp(EAT, str) == 0)
	{
		state += pthread_mutex_lock(&philo->lock);
		philo->last_meal = time;
		state += pthread_mutex_unlock(&philo->lock);
	}
	state += pthread_mutex_unlock(&philo->dt->deadlock);
	if (state != 0)
		ft_error(-6, philo->dt);
	return (time);
}
