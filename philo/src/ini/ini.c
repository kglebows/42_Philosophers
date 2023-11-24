/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:16:22 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/24 15:21:16 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	n;

	n = 0;
	while (s1[n] != 0)
		n++;
	while (n--)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		else if ((unsigned char)*s1 == '\0' || (unsigned char)*s2 == '\0')
			break ;
		s1++;
		s2++;
	}
	return (0);
}

t_philo	*create_philo(int id, t_dt *dt)
{
	t_philo			*philo;
	int				state;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		ft_error(-4, dt);
	philo->dt = dt;
	philo->id = id;
	state = pthread_mutex_init(&philo->lock, NULL);
	state += pthread_mutex_lock(&philo->lock);
	philo->happy = 0;
	philo->last_meal = ft_time(dt);
	state += pthread_mutex_unlock(&philo->lock);
	philo->right = ft_calloc(1, sizeof(t_philo));
	if (!philo->right)
		ft_error(-4, dt);
	philo->right->id = id * -1;
	state += pthread_mutex_init(&philo->right->lock, NULL);
	philo->right->left = philo;
	if (state != 0)
		ft_error(-17, dt);
	return (philo);
}

void	start_threads(t_dt *dt)
{
	t_philo			*spot;
	int				state;

	state = pthread_create(&dt->philo->philo, NULL, ft_philo, dt->philo);
	spot = dt->philo->right;
	while (spot != dt->philo)
	{
		if (spot->id > 0)
			state += pthread_create(&spot->philo, NULL, ft_philo, spot);
		spot = spot->right;
	}
	if (state != 0)
		ft_error(-18, dt);
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
	int			state;

	state = pthread_mutex_init(&dt->timelock, NULL);
	if (argn < 5)
		ft_error(-1, dt);
	if (argn > 6)
		ft_error(-2, dt);
	ft_ini_arguments(argn, argc, dt);
	create_round_table(dt);
	dt->start_time = ft_time(dt);
	state += pthread_mutex_init(&dt->deadlock, NULL);
	start_threads(dt);
	if (state != 0)
		ft_error(-19, dt);
}
