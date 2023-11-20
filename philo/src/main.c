/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/20 16:50:42 by kglebows         ###   ########.fr       */
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
		if (ft_time(0, &dt) - temp->last_meal >= dt.time_to_die)
		{
			printf("%lld %d died\n", ft_time(1, &dt), temp->id);
			pthread_mutex_unlock(&temp->lock);
			ft_exit(&dt);
			// philo->status = 4;
			// // pthread_mutex_lock(&philo->dt->deadlock);
			// // pthread_mutex_lock(&philo->dt->timelock);
			// break ;
		}
		pthread_mutex_unlock(&temp->lock);
		temp = temp->right->right;
	}
	// ft_exit(&dt);
	return (0);
}
