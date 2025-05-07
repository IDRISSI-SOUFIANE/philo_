/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:03:36 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/07 10:40:48 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incldue/philo.h"

void	fill_input(t_philo *philo, char **av)
{
	philo->num_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->num_time_to_eat = ft_atoi(av[5]);
	else
		philo->num_time_to_eat = -1;
}

int	init_philos(t_program *program, t_philo *philo, pthread_mutex_t *forks,
			char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		fill_input(&philo[i], av);
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].write_lock = &program->write_lock;
		philo[i].dead = &program->dead_flag;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1 ) % ft_atoi(av[1])];
		i++;
	}
	return (0);
}

int	init_forks(pthread_mutex_t *forks, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (write(2, "Error in init_forks\n", 22), i);
		i++;
	}
	return (0);
}

int	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	if (pthread_mutex_init(&program->dead_lock, NULL))
		return (write(2, "Error in init_program\n", 23), 1);
	if (pthread_mutex_init(&program->meal_lock, NULL))
		return (write(2, "Error in init_program\n", 23), 2);
	if (pthread_mutex_init(&program->write_lock, NULL))
		return (write(2, "Error in init_program\n", 23), 3);
	return (0);
}
