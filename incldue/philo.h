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


// utils
long	ft_atoi(char *str);
int		is_not_digit(char *av);
long	get_current_time(void);
void	precise_usleep(long duration_ms);
int		ft_strcmp(char *s1, char *s2);

//init
int	init_program(t_program *program, t_philo *philos);
int	init_forks(pthread_mutex_t *forks, int n_philo);
int	init_philos(t_program *program, t_philo *philo, pthread_mutex_t *forks,
			char **av);


// thread.c
int	creat_thread(t_program *program, pthread_mutex_t *forks);

//helper_thread.c
int		check_death(t_philo *philo);
void	write_message(char *str, t_philo *philo, int id);

// manage.c
void    *manage(void *arg);

// helper_thread

/*helper_threas*/
int destroy(t_program *program, pthread_mutex_t *forks);
#endif