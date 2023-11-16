/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:16:22 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/16 18:51:46 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*time_now(void *data)
{
	t_dt				*dt;
	struct timeval		now;

	dt = (t_dt *) data;
	while (1)
	{
		gettimeofday(&now, NULL);
		dt->time = (now.tv_sec - dt->start_time.tv_sec) * 1000L +
				(now.tv_usec - dt->start_time.tv_usec) / 1000L;
	}
}

t_philo	*create_philo(int id, t_dt *dt)
{
	t_philo			*philo;

	philo = calloc(1, sizeof(t_philo));
	if (!philo)
		ft_error(-4, dt);
	philo->id = id;
	philo->right = calloc(1, sizeof(t_philo));
	if (!philo->right)
		ft_error(-4, dt);
	philo->right->id = id * -1;
	philo->right->left = philo;
	return (philo);
}

void	create_round_table(t_dt *dt)
{
	int			i;
	t_philo		*spot;

	dt->philo = create_philo(1, dt);
	spot = dt->philo->right;
	i = 2;
	while (i <= dt->number_of_philosophers)
	{
		spot->right = create_philo(i, dt);
		spot->right->left = spot;
		spot = spot->right->right;
		i++;
	}
	spot->right = dt->philo;
	dt->philo->left = spot;
}

void	ft_ini(int argn, char *argc[], t_dt *dt)
{
	gettimeofday(&dt->start_time, NULL);
	pthread_create(&dt->the_time_itself, NULL, time_now, dt);
	if (argn < 5)
		ft_error(-1, dt);
	if (argn > 6)
		ft_error(-2, dt);
	ft_ini_arguments(argn, argc, dt);
	create_round_table(dt);
	printf("%d :: %d :: %d :: %d :: %d\n", dt->number_of_philosophers, dt->time_to_die, dt->time_to_eat, dt->time_to_sleep, dt->number_of_times_each_philosopher_must_eat);
}
