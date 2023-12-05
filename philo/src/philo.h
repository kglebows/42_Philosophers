/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:12:23 by kglebows          #+#    #+#             */
/*   Updated: 2023/12/05 20:51:50 by kglebows         ###   ########.fr       */
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

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

struct	s_dt;

/**
 * @brief Data structure representing spots around the philosophers
 * table. Contains philosophers and forks.
 * @param id Positive value is philosopher, negative value is fork
 * @param dt Pointer to program main data
 * @param philo Philosophers thread
 * @param lock Mutex for fork management and data racing prevention
 * @param meals_had amount of meals eaten by the philosopher
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
	int					meals_had;
	int					happy;
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
 * @param must_eat number of times each philospher must eat
 * @param happy_philo 1 - Philosopher has eaten requierd amount of meals
 * @param timelock The mutex for tracking time
 * @param start_time Time of starting the program
 * @param deadlock Mutex for dead philosopher and exiting program
 * @param exit 1 - Program is in exit stage
 * @param philo Pointer to the first philosopher
 */
typedef struct s_dt
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					happy_philo;
	pthread_mutex_t		timelock;
	long long			start_time;
	pthread_mutex_t		deadlock;
	int					exit;
	t_philo				*philo;
}						t_dt;

void		ft_ini(int argn, char *argc[], t_dt *dt);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_strncmp(const char *s1, const char *s2);
long long	ft_time(t_dt *dt);
long long	ft_say(char *str, t_philo *philo);
void		*ft_philo(void *data);
void		ft_ini_arguments(int argn, char *argc[], t_dt *dt);

/**
 * @brief Exit function in case of an error.
 * @param[in] code Error code for displaying exit message.
*/
void		ft_error(int code, t_dt *dt);
void		ft_exit(t_dt *dt);

#endif