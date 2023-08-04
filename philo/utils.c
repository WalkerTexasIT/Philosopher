/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:57:46 by brminner          #+#    #+#             */
/*   Updated: 2023/08/03 18:44:49 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void ft_usleep(long long int time)
{
	long long int	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(100);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print);
	printf("%lld %d %s\n", ft_get_time() - philo->start, philo->id, str);
	pthread_mutex_unlock(philo->print);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atol(char *str)
{
	int		i;
	long long	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}

int	ft_atoi(char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}
