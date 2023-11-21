/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:16:22 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/21 16:14:52 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(t_dt *dt)
{
	int					state;
	struct timeval		now;
	long long			time;

	state = 0;
	state += pthread_mutex_lock(&dt->timelock);
	state += gettimeofday(&now, NULL);
	time = now.tv_sec * 1000L + now.tv_usec / 1000L - dt->start_time;
	state += pthread_mutex_unlock(&dt->timelock);
	if (state > 0)
		ft_error(-5, dt);
	return (time);
}

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

long long	ft_say(char *str, t_philo *philo)
{
	long long		time;
	int				state;

	state = pthread_mutex_lock(&philo->dt->deadlock);
	time = ft_time(philo->dt);
	if (philo->dt->exit == 0)
		printf("%lld %d %s\n", time, philo->id, str);
	if (ft_strncmp(EAT, str) == 0)
	{
		state += pthread_mutex_lock(&philo->lock);
		philo->last_meal = time;
		philo->meals_had++;
		state += pthread_mutex_unlock(&philo->lock);
	}
	if (ft_strncmp(DEAD, str) == 0)
		philo->dt->exit = 1;
	state += pthread_mutex_unlock(&philo->dt->deadlock);
	if (state != 0)
		ft_error(-6, philo->dt);
	return (time);
}
// void	*time_now(void *data)
// {
// 	t_dt				*dt;

// 	pthread_mutex_init(&timelock, NULL);
// 	dt = (t_dt *) data;
// 	while (1)
// 	{

// 	}
// }

t_philo	*create_philo(int id, t_dt *dt)
{
	t_philo			*philo;
	int				state;

	philo = calloc(1, sizeof(t_philo));
	if (!philo)
		ft_error(-4, dt);
	philo->dt = dt;
	philo->id = id;
	state = pthread_mutex_init(&philo->lock, NULL);
	// pthread_create(&philo->philo, NULL, ft_philo, philo);
	state += pthread_mutex_lock(&philo->lock);
	philo->happy = 0;
	philo->last_meal = ft_time(dt);
	state += pthread_mutex_unlock(&philo->lock);
	philo->right = calloc(1, sizeof(t_philo));
	if (!philo->right)
		ft_error(-4, dt);
	state += pthread_mutex_init(&philo->right->lock, NULL);
	philo->right->id = id * -1;
	philo->right->left = philo;
	if (state != 0)
		ft_error(-7, dt);
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
		ft_error(-8, dt);
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
	// pthread_create(&dt->the_time_itself, NULL, time_now, dt);
	if (argn < 5)
		ft_error(-1, dt);
	if (argn > 6)
		ft_error(-2, dt);
	ft_ini_arguments(argn, argc, dt);
	create_round_table(dt);
	dt->start_time = ft_time(dt);
	// gettimeofday(&dt->start_time, NULL);
	start_threads(dt);
	state += pthread_mutex_init(&dt->deadlock, NULL);
	if (state != 0)
		ft_error(-9, dt);
	// printf("%d :: %d :: %d :: %d :: %d\n", dt->number_of_philosophers, dt->time_to_die, dt->time_to_eat, dt->time_to_sleep, dt->number_of_times_each_philosopher_must_eat);
}
