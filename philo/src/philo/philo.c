/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:56:17 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/22 16:25:29 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *data)
{
	int					state;
	t_philo				*philo;
	long long			time;

	philo = (t_philo *) data;
	while (1)
	{
		state = pthread_mutex_lock(&philo->dt->deadlock);
		if (state != 0)
			printf("::1::");
		if (philo->dt->exit == 1)
		{
			state += pthread_mutex_unlock(&philo->dt->deadlock);
			if (state != 0)
				printf("::2::");
			break ;
		}
		state += pthread_mutex_unlock(&philo->dt->deadlock);
			if (state != 0)
			printf("::3::");
		state += pthread_mutex_lock(&philo->lock);
			if (state != 0)
			printf("::4::");
		if (philo->id % 2 == 1 && philo->meals_had == 0)
			usleep(philo->dt->time_to_eat * 500);
		state += pthread_mutex_unlock(&philo->lock);
			if (state != 0)
			printf("::5::");
		state += pthread_mutex_lock(&philo->right->lock);
			if (state != 0)
			printf("::6::");
		ft_say(FORK, philo);
		state += pthread_mutex_lock(&philo->left->lock);
			if (state != 0)
			printf("::7::");
		ft_say(FORK, philo);
		time = ft_say(EAT, philo);
		while (ft_time(philo->dt) - time < philo->dt->time_to_eat)
			usleep(200);
		state += pthread_mutex_unlock(&philo->right->lock);
			if (state != 0)
			printf("::8::");
		state += pthread_mutex_unlock(&philo->left->lock);
			if (state != 0)
			printf("::9::");
		state += pthread_mutex_lock(&philo->lock);
			if (state != 0)
			printf("::10::");
		philo->meals_had++;
		state += pthread_mutex_unlock(&philo->lock);
			if (state != 0)
			printf("::11::");
		ft_say(SLEEP, philo);
		while (ft_time(philo->dt) - philo->last_meal < philo->dt->time_to_sleep + philo->dt->time_to_eat)
			usleep(200);
		ft_say(THINK, philo);
		if (state != 0)
		{
			printf("exit code: %d", state);
			ft_error(-10, philo->dt);
		}
	}
	pthread_mutex_destroy(&philo->lock);
	return (philo);
}

