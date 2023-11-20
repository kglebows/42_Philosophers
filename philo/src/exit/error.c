/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:29:04 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/19 15:01:16 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error__(int code, t_dt *dt)
{
	if (code == -23)
		printf("Error! \n");
	else
		printf("Error! Error code missing!\n");
	(void)dt;
}

void	error_(int code, t_dt *dt)
{
	if (code == -12)
		printf("Error! \n");
	else if (code == -13)
		printf("Error! \n");
	else if (code == -14)
		printf("Error! \n");
	else if (code == -15)
		printf("Error! \n");
	else if (code == -16)
		printf("Error! \n");
	else if (code == -17)
		printf("Error! \n");
	else if (code == -18)
		printf("Error! \n");
	else if (code == -19)
		printf("Error! \n");
	else if (code == -20)
		printf("Error! \n");
	else if (code == -21)
		printf("Error! \n");
	else if (code == -22)
		printf("Error! \n");
	else
		error__(code, dt);
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
		printf("Error! Failed to allocate memory!\n");
	else if (code == -5)
		printf("Error! Time mutex failure!\n");
	else if (code == -6)
		printf("Error! \n");
	else if (code == -7)
		printf("Error! \n");
	else if (code == -8)
		printf("Error! \n");
	else if (code == -9)
		printf("Error! \n");
	else if (code == -10)
		printf("Error! \n");
	else if (code == -11)
		printf("Error! \n");
	else
		error_(code, dt);
	ft_exit(dt);
}
