/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:09:35 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/06 09:24:55 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incldue/philo.h"

static int valid_input(char **av)
{
	if (ft_atoi(av[1]) > 420 || ft_atoi(av[1]) <= 0 || is_not_digit(av[1]))
		return (write(2, "Invalid Philosophes number\n", 28), 1);
	if (ft_atoi(av[2]) <= 0 || is_not_digit(av[2]))
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(av[3]) <= 0 || is_not_digit(av[3]))
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(av[4]) <= 0 || is_not_digit(av[4]))
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || is_not_digit(av[5])))
		return (write(2, "Invalid number of times each philosopher must eat\n",
					51),
				1);
	return (0);
}

void	f()
{
	system("leaks ./a.out");
}


int main(int ac, char **av)
{
	// atexit(f);
	t_program		program;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long			n_philo;

	if (ac < 5 || ac > 6)
		return (write(2, "Wrong encounter numbers\n", 25), 1);
	if (valid_input(av))
		return (1);
		
	n_philo = ft_atoi(av[1]);
	philos = malloc(sizeof(t_philo) * n_philo);
	if (!philos)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!forks)
		return (free(philos), 1);

	if (init_program(&program, philos))
		return (free(philos), free(forks), 1);
	if (init_forks(forks, ft_atoi(av[1])))
		return (free(philos), free(forks), 1);
	if (init_philos(&program, philos, forks, av))
		return (free(philos), free(forks), 1);

	if (creat_thread(&program, forks))
		return (free(philos), free(forks), 1);
	destroy(&program, forks);
	free(philos);
	free(forks);
	return (0);
}

// I can use ft_destroy("fail create thread\n", philos, program, forks)