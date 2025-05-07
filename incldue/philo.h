/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:25:35 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/07 11:26:30 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>


typedef	struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	long			last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_philos;
	int				num_time_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_program;


long	ft_atoi(char *str);
int		is_not_digit(char *av);
long	get_current_time(void);
void	precise_usleep(long duration_ms);
int		ft_strcmp(char *s1, char *s2);

int		init_program(t_program *program, t_philo *philos);
int		init_forks(pthread_mutex_t *forks, int n_philo);
int		init_philos(t_program *program, t_philo *philo, pthread_mutex_t *forks,
			char **av);

void    *manage(void *arg);
int		creat_thread(t_program *program, pthread_mutex_t *forks);

int		check_death(t_philo *philo);
void	write_message(char *str, t_philo *philo, int id);
int		destroy( t_program *program, pthread_mutex_t *forks, int index, int flag);
#endif