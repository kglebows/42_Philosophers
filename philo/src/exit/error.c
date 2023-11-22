/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:29:04 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/22 14:32:26 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(int code, t_dt *dt)
{
	if (code == -1)
		printf("Error! Too few arguments!\n");
	else if (code == -2)
		printf("Error! Too many arguments!\n");
	else if (code == -3)
		printf("Error! Wrong input!\n");
	else if (code == -4)
		printf("Error! Failed to allocate memory!\n");
	else if (code == -5)
		printf("Error! Time mutex failure!\n");
	else if (code == -6)
		printf("Error! Say mutex failure!\n");
	else if (code == -7)
		printf("Error! Create Philosopher mutex failure!\n");
	else if (code == -8)
		printf("Error! Thread starter failure!\n");
	else if (code == -9)
		printf("Error! Initialization mutex failure!\n");
	else if (code == -10)
		printf("Error! Philosopher thread mutex failure!\n");
	if (code < -2)
		ft_exit(dt);
	else
		exit(0);
}
