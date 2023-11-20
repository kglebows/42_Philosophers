/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/20 15:41:05 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argn, char *argc[])
{
	t_dt				dt;
	t_philo				*temp;

	ft_ini(argn, argc, &dt);
	temp = dt.philo;
	while (1)
	{
		pthread_mutex_lock(&temp->lock);
		if (ft_time(&dt) - temp->last_meal >= dt.time_to_die)
		{
			printf("%lld %d died\n", ft_time(&dt), temp->id);
			pthread_mutex_lock(&dt.deadlock);
			pthread_mutex_lock(&dt.timelock);
			ft_exit(&dt);
			// philo->status = 4;
			// // pthread_mutex_lock(&philo->dt->deadlock);
			// // pthread_mutex_lock(&philo->dt->timelock);
			// break ;
		}
		pthread_mutex_unlock(&temp->lock);
		temp = temp->right;
	}
	// ft_exit(&dt);
	return (0);
}
