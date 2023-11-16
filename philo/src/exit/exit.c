/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:06:09 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/16 18:47:41 by kglebows         ###   ########.fr       */
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

void	ft_exit(t_dt *dt)
{
	free_spots(dt);
	pthread_detach(dt->the_time_itself);
	system("leaks philo");
	exit(0);
}
