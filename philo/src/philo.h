/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:12:23 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/16 18:42:01 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/**
 * @brief Data structure representing spots around the philosophers
 * table. Contains philosophers and forks.
 * @param id Positive value is philosopher, negative value is fork
 * @param left Fork/Philosopher on the left
 * @param right Fork/Philosopher on the right
 */
typedef struct s_philo
{
	int					id;
	struct s_philo		*left;
	struct s_philo		*right;
}						t_philo;

/**
 * @brief Main data structure that holds all information needed for the program.
 * @param number_of_philosophers how many philosophers there are
 * @param time_to_die time without eating that philosopher can survive
 * @param time_to_eat time that takes philosopher to eat
 * @param time_to_sleep time that takes philosopher to sleep after eating
 * @param number_of_times_each_philosopher_must_eat a minimal value of meals
 * @param the_time_itself The thread tracking time
 * @param start_time Time of starting the program
 * @param time Running time in miliseconds.
 * @param philo Pointer to the first philosopher
 */
typedef struct s_dt
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	pthread_t			the_time_itself;
	struct timeval		start_time;
	long long			time;
	t_philo				*philo;
}						t_dt;


void	ft_ini(int argn, char *argc[], t_dt *dt);

/**
 * @brief Exit function in case of an error.
 * @param[in] code Error code for displaying exit message.
*/
void	ft_error(int code, t_dt *dt);
void	ft_exit(t_dt *dt);

void	ft_ini_arguments(int argn, char *argc[], t_dt *dt);


#endif