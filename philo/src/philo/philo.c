/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:56:17 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/21 16:06:20 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fork(t_philo *philo, t_philo *fork)
{
	pthread_mutex_lock(&fork->lock);
	ft_say(FORK, philo);
	// printf("%lld %d has taken a fork\n", ft_time(0, philo->dt), philo->id);
}

// void	ft_eat(t_philo *philo)
// {
// 	long long	eat_time;

// 	if (philo->id % 2 == 1)
// 		usleep(philo->dt->time_to_eat * 500);
// 	ft_fork(philo, philo->right);
// 	ft_fork(philo, philo->left);
// 	eat_time = ft_say(EAT, philo);
// 	// eat_time = ft_time(0, philo->dt);
// 	// printf("%lld %d is eating\n", eat_time, philo->id);
// 	while (ft_time(philo->dt) - eat_time < philo->dt->time_to_eat)
// 		usleep(200);
// 	// usleep(philo->dt->time_to_eat * 1000);
// 	// philo->meals_had++;
// 	pthread_mutex_unlock(&philo->right->lock);
// 	pthread_mutex_unlock(&philo->left->lock);
// 	ft_say(SLEEP, philo);
// 	usleep(philo->dt->time_to_sleep * 1000);
// 	// printf("%lld %d is sleeping\n", philo->last_meal, philo->id);
// 	// while (ft_time(philo->dt) - philo->last_meal < philo->dt->time_to_sleep)
// 	// 	;
// 	ft_say(THINK, philo);
// 	// printf("%lld %d is thinking\n", ft_time(0, philo->dt), philo->id);
// }

void	*ft_philo(void *data)
{
	t_philo				*philo;
	long long			time;

	philo = (t_philo *) data;
	// pthread_mutex_init(&philo->lock, NULL);
	// printf("%lld :: Philosopher %d exists\n", philo->dt->time, philo->id);
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->id % 2 == 1 && philo->meals_had == 0)
			usleep(philo->dt->time_to_eat * 500);
		pthread_mutex_unlock(&philo->lock);
		ft_fork(philo, philo->right);
		ft_fork(philo, philo->left);
		time = ft_say(EAT, philo);
		// eat_time = ft_time(0, philo->dt);
		// printf("%lld %d is eating\n", eat_time, philo->id);
		while (ft_time(philo->dt) - time < philo->dt->time_to_eat)
			usleep(200);
		// usleep(philo->dt->time_to_eat * 1000);
		// philo->meals_had++;
		pthread_mutex_unlock(&philo->right->lock);
		pthread_mutex_unlock(&philo->left->lock);
		// pthread_mutex_lock(&philo->lock);
		ft_say(SLEEP, philo);
		// usleep(philo->dt->time_to_sleep * 1000);
		// printf("%lld %d is sleeping\n", philo->last_meal, philo->id);
		while (ft_time(philo->dt) - philo->last_meal < philo->dt->time_to_sleep + philo->dt->time_to_eat)
			usleep(200);
		ft_say(THINK, philo);
		// pthread_mutex_unlock(&philo->lock);
	}
	
	// if (philo->dt->dead == 0)
	// {	
	// }
	// pthread_mutex_unlock(&philo->dt->deadlock);
	// else
	// 	printf("%lld :: Philosopher %d cries after %d death and leaves.\n", philo->dt->time, philo->	, philo->dt->dead);
	// while (1)
	// 	;
	return (philo);
}
