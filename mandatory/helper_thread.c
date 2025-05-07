/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:44:33 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/07 11:08:27 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incldue/philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo[0].dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	write_message(char *str, t_philo *philo, int id)
{
	long	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!ft_strcmp(str, "died"))
		printf("%lu {%d} %s\n", time, id, str);
	else if (!check_death(philo))
	{
		if (!str)
		{
			pthread_mutex_unlock(philo->write_lock);
			return ;
		}
		else
			printf("%lu {%d} %s\n", time, id, str);
	}
	pthread_mutex_unlock(philo->write_lock);
}

int	destroy_program(t_program *program, int index)
{
	if (index == 1)
		if (pthread_mutex_destroy(&program->dead_lock))
			return (write(2, "Error in mutex_destroy function 1\n", 35), 1);
	if (index == 2)
		if (pthread_mutex_destroy(&program->meal_lock))
			return (write(2, "Error in mutex_destroy function 1\n", 35), 1);
	if (index == 3)
		if (pthread_mutex_destroy(&program->write_lock))
			return (write(2, "Error in mutex_destroy function 1\n", 35), 1);
	return (0);
}

int	destroy_forks(t_program *program, pthread_mutex_t *forks, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (pthread_mutex_destroy(&forks[i]))
			return (write(2, "Error in mutex_destroy function 1\n", 35), 1);
		i++;
	}
	return (0);
}

int destroy(t_program *program, pthread_mutex_t *forks, int index, int flag)
{
	int i;

	i = 0;
	if (flag == 0)
		return (destroy_program(program, index));
	else if (flag == 1)
		destroy_forks(program, forks, index);
	else
	{
		if (pthread_mutex_destroy(&program->write_lock))
			return (write(2, "Error in mutex_destroy function 1\n", 35), 1);
		if (pthread_mutex_destroy(&program->meal_lock))
			return (write(2, "Error in mutex_destroy function 2\n", 35), 1);
		if (pthread_mutex_destroy(&program->dead_lock))
			return (write(2, "Error in mutex_destroy function 3\n", 35), 1);
		while (i < program->philos[0].num_philos)
		{
			if (pthread_mutex_destroy(&forks[i]))
				return (write(2, "Error in mutex_destroy function 8\n", 35), 1);
			i++;
		}
	}
	return (0);
}