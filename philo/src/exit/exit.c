/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:06:09 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/24 15:20:35 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_spots(t_dt *dt)
{
	t_philo			*spot;
	t_philo			*temp;

	spot = dt->philo;
	while (1)
	{
		temp = spot->right;
		free(spot);
		spot = temp;
		if (spot == dt->philo)
			break ;
	}
}

void	philosophers_go_byebye(t_dt *dt)
{
	int			i;
	t_philo		*spot;

	spot = dt->philo;
	i = 0;
	while (i < dt->number_of_philosophers)
	{
		(void) pthread_join(spot->philo, NULL);
		spot = spot->right->right;
		i++;
		usleep(200);
	}
}

void	ft_exit(t_dt *dt)
{
	pthread_mutex_unlock(&dt->deadlock);
	philosophers_go_byebye(dt);
	free_spots(dt);
	pthread_mutex_destroy(&dt->timelock);
	pthread_mutex_destroy(&dt->deadlock);
	exit(0);
}
