/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:29:04 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/24 15:08:55 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_(int code)
{
	if (code == -10)
		printf("Error! Philosopher thread mutex failure!\n");
	else if (code == -11)
		printf("Error! Main program mutex failure!\n");
	else if (code == -12)
		printf("Error! \n");
	else if (code == -13)
		printf("Error! \n");
	else if (code == -14)
		printf("Error! Failed to allocate memory!\n");
	else if (code == -15)
		printf("Error! Time mutex failure!\n");
	else if (code == -16)
		printf("Error! Say mutex failure!\n");
	else if (code == -17)
		printf("Error! Create Philosopher mutex failure!\n");
	else if (code == -18)
		printf("Error! Thread starter failure!\n");
	else if (code == -19)
		printf("Error! Initialization mutex failure!\n");
	else
		printf("Error! Unknown error code %d!\n", code);
}

void	ft_error(int code, t_dt *dt)
{
	if (code == -1)
		printf("Error! Too few arguments!\n");
	else if (code == -2)
		printf("Error! Too many arguments!\n");
	else if (code == -3)
		printf("Error! Wrong input!\n");
	else if (code == -4)
		printf("Error! The number of meals has to be bigger than 0!\n");
	else if (code == -5)
		printf("Error! The number of philosophers must be bigger than 0!\n");
	else if (code == -6)
		printf("Error! The time has to be bigger than 0!\n");
	else if (code == -7)
		printf("0 1 has taken a fork\n%d 1 died\n", dt->time_to_die);
	else if (code == -8)
		printf("Error! \n");
	else if (code == -9)
		printf("Error! \n");
	else
		error_(code);
	if (code < -9)
		ft_exit(dt);
	else
		exit(0);
}
