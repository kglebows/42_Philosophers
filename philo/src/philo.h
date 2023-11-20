/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:12:23 by kglebows          #+#    #+#             */
/*   Updated: 2023/11/20 12:02:56 by kglebows         ###   ########.fr       */
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

struct s_dt;

/**
 * @brief Data structure representing spots around the philosophers
 * table. Contains philosophers and forks.
 * @param id Positive value is philosopher, negative value is fork
 * @param dt Pointer to program main data
 * @param philo Philosophers thread
 * @param status 1 - Think 2 - Eat 3 - Sleep 4 - Dead -1 - Fork free -2 - Fork taken
 * @param last_meal Time of last meal
 * @param left Fork/Philosopher on the left
 * @param right Fork/Philosopher on the right
 */
typedef struct s_philo
{
	int					id;
	struct s_dt			*dt;
	pthread_t			philo;
	pthread_mutex_t		lock;
	int					status;
	long long			last_meal;
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
 * @param deadlock Mutex for dead philosopher
 * @param philo Pointer to the first philosopher
 */
typedef struct s_dt
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	pthread_mutex_t		timelock;
	struct timeval		start_time;
	pthread_mutex_t		deadlock;
	t_philo				*philo;
}						t_dt;


void	ft_ini(int argn, char *argc[], t_dt *dt);

long long ft_time(t_dt *dt);

void	*ft_philo(void *data);

/**
 * @brief Exit function in case of an error.
 * @param[in] code Error code for displaying exit message.
*/
void	ft_error(int code, t_dt *dt);
void	ft_exit(t_dt *dt);

void	ft_ini_arguments(int argn, char *argc[], t_dt *dt);


#endif