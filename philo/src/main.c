/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/21 15:31:41 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_counter(t_philo *philo)
{
	int				i;

	i = philo->dt->number_of_times_each_philosopher_must_eat;
	if (i > 0 && philo->happy == 0)
	{
		if (philo->meals_had >= i)
		{
			philo->dt->happy_philo++;
			philo->happy = 1;
		}
	}
	if (i == 0 || philo->dt->happy_philo == philo->dt->number_of_philosophers)
		ft_exit(philo->dt);
}

int	main(int argn, char *argc[])
{
	t_dt				dt;
	t_philo				*temp;

	ft_ini(argn, argc, &dt);
	temp = dt.philo;
	// printf("enterin main loop\n");
	while (1)
	{
		pthread_mutex_lock(&temp->lock);
		// printf("checking %d \n", temp->id);
		if (ft_time(&dt) - temp->last_meal >= dt.time_to_die)
		{
			ft_say(DEAD, temp);
			pthread_mutex_unlock(&temp->lock);
			break ;
		}
		meal_counter(temp);
		pthread_mutex_unlock(&temp->lock);
		temp = temp->right->right;
		usleep(200);
	}
	ft_exit(&dt);
	return (0);
}
