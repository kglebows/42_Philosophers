/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:26:44 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/16 18:52:03 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void test_spots(t_dt *dt)
{
	t_philo		*spot;
	int			i;

	spot = dt->philo;
	i = 0;
	while (i < 4)
	{
		printf("%lld # ID : %d\n", dt->time, spot->id);
		usleep(1000000);
		spot = spot->right;
		i++;
	}
	
}

int	main(int argn, char *argc[])
{
	t_dt				dt;

	ft_ini(argn, argc, &dt);
	test_spots(&dt);
	ft_exit(&dt);
	return (0);
}
