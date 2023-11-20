/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:56:17 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/20 16:49:17 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fork(t_philo *philo, t_philo *fork)
{
	pthread_mutex_lock(&fork->lock);
	printf("%lld %d has taken a fork\n", ft_time(0, philo->dt), philo->id);
}

void	ft_eat(t_philo *philo)
{
	long long	eat_time;

	if (philo->id % 2 == 1)
		usleep(1000);
	ft_fork(philo, philo->right);
	ft_fork(philo, philo->left);
	eat_time = ft_time(0, philo->dt);
	printf("%lld %d is eating\n", eat_time, philo->id);
	while (ft_time(0, philo->dt) - eat_time < philo->dt->time_to_eat)
		;
	pthread_mutex_unlock(&philo->right->lock);
	pthread_mutex_unlock(&philo->left->lock);
	philo->last_meal = ft_time(0, philo->dt);
	printf("%lld %d is sleeping\n", philo->last_meal, philo->id);
	while (ft_time(0, philo->dt) - philo->last_meal < philo->dt->time_to_sleep)
		;
	printf("%lld %d is thinking\n", ft_time(0, philo->dt), philo->id);
}

void	*ft_philo(void *data)
{
	t_philo				*philo;

	philo = (t_philo *) data;
	// pthread_mutex_init(&philo->lock, NULL);
	// printf("%lld :: Philosopher %d exists\n", philo->dt->time, philo->id);
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		// if (ft_time(philo->dt) - philo->last_meal >= philo->dt->time_to_die)
		// {
		// 	printf("%lld %d died\n", ft_time(philo->dt), philo->id);
		// 	philo->status = 4;
		// 	// pthread_mutex_lock(&philo->dt->deadlock);
		// 	// pthread_mutex_lock(&philo->dt->timelock);
		// 	break ;
		// }
		// else
			ft_eat(philo);
		pthread_mutex_unlock(&philo->lock);
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
