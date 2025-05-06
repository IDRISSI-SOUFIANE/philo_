/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:47:20 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/03 20:39:36 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incldue/philo.h"

void	think(t_philo *philo)
{
	write_message("is thinking", philo, philo->id);
}

void	sleeeeep(t_philo *philo)
{
	write_message("is sleeping", philo, philo->id);
	precise_usleep(philo->time_to_sleep);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	write_message("is took a fork", philo, philo->id);
	// case sensitive 
	if (philo->num_philos == 1)
	{
		precise_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	write_message("is took a fork", philo, philo->id);
	write_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	precise_usleep(philo->time_to_eat);
	philo->eating = 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	
	if (philo->id % 2 == 0)
		precise_usleep(philo->time_to_eat / 2);
	while (!check_death(philo))
	{
		eat(philo);
		sleeeeep(philo);
		think(philo);
	}
	return (NULL);
}

int	creat_thread(t_program *program, pthread_mutex_t *forks)
{
	pthread_t   super_visour;
	int         i;

	i = 0;
	if (pthread_create(&super_visour, NULL, &manage, program->philos))
		return(destroy(program, forks), 1);
	while (i < program->philos[0].num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine, &program->philos[i]))
			return(destroy(program, forks), 1);
		i++;
	}
	i = 0;
	if (pthread_join(super_visour, NULL))
		return(destroy(program, forks), 1);
	while (i < program->philos[0].num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
		{
			destroy(program, forks);
			return (1);
		}
	}
	return (0);
}
