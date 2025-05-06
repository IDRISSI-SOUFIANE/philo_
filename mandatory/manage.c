/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:46:11 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/03 10:59:45 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incldue/philo.h"


int	 check_if_there_death(t_philo *philo)
{
	int		i;
	long	since_last_meal;

	i = 0;
	while (i < philo[0].num_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		since_last_meal = get_current_time() - philo[i].last_meal;
		pthread_mutex_unlock(philo[i].meal_lock);
		if (since_last_meal >= philo[i].time_to_die)
		{
			pthread_mutex_lock(philo[0].dead_lock);
			if (*philo[0].dead == 0)
			{
				*philo[0].dead = 1;
				pthread_mutex_unlock(philo[0].dead_lock);
				write_message("died", &philo[i], philo[i].id);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philo)
{
	int	i;
	int	all_ate;

	all_ate = 0;
	i = 0;
	while (i < philo[0].num_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[0].num_time_to_eat)
			all_ate++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (all_ate == philo[0].num_time_to_eat)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo[0].dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void    *manage(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	
	while (1337)
		if (check_if_all_ate(philo) || check_if_there_death(philo))
			break ;
	return (NULL);
}