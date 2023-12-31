/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:17:23 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/06 14:06:03 by kglebows         ###   ########.fr       */
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
		ft_error(-15, dt);
	return (time);
}

void	happy_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->dt->happylock);
	philo->happy++;
	philo->dt->happy_philo++;
	if (philo->dt->happy_philo == philo->dt->number_of_philosophers)
		philo->dt->exit = 1;
	pthread_mutex_unlock(&philo->dt->happylock);
}

long long	ft_say(char *str, t_philo *philo)
{
	long long		time;
	int				state;

	state = pthread_mutex_lock(&philo->dt->deadlock);
	time = ft_time(philo->dt);
	if (philo->dt->exit == 0
		&& philo->dt->happy_philo != philo->dt->number_of_philosophers)
		printf("%lld %d %s\n", time, philo->id, str);
	if (ft_strncmp(EAT, str) == 0)
	{
		state += pthread_mutex_lock(&philo->lock);
		philo->last_meal = time;
		philo->meals_had++;
		if (philo->meals_had == philo->dt->must_eat)
			happy_end(philo);
		state += pthread_mutex_unlock(&philo->lock);
	}
	state += pthread_mutex_unlock(&philo->dt->deadlock);
	if (state != 0)
		ft_error(-16, philo->dt);
	return (time);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = s;
	while (n--)
		*str++ = '\0';
}
