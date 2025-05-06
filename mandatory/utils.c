/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:29:39 by sidrissi          #+#    #+#             */
/*   Updated: 2025/05/02 22:20:23 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incldue/philo.h"

long ft_atoi(char *str)
{
	long res;
	int sign;

	sign = 1;
	res = 0;

	while ((*str > 9 && *str < 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = res * 10 + (*str - '0');
		if ((sign == 1 && res > INT_MAX )||
			(sign == -1 && res > ((long)INT_MAX + 1)))
			return (-1);
		str++;
	}
	return (res * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (s1[i] - s2[i]);
}

int	is_not_digit(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!(av[i] >= '0' && av[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

long get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


void	precise_usleep(long duration_ms)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < duration_ms)
		usleep(500);
}