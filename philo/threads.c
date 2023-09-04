/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:09:05 by brminner          #+#    #+#             */
/*   Updated: 2023/09/04 18:26:24 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->in->mut_dead);
	if (philo->in->dead == 1)
	{
		pthread_mutex_unlock(&philo->in->mut_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->in->mut_dead);
	pthread_mutex_lock(philo->print);
	printf("%lld %d %s\n", ft_get_time() - philo->start, philo->id, str);
	pthread_mutex_unlock(philo->print);
}

int	ft_detach_threads(t_in *in)
{
	int	i;

	i = 0;
	while (i < in->nb_philo)
	{
		if (pthread_detach(in->philo[i].thread) != 0)
			return (0);
		i++;
	}
	return (0);
}

int	ft_join_threads(t_in *in)
{
	int	i;

	i = 0;
	while (i < in->nb_philo)
	{
		if (pthread_join(in->philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_create_threads(t_in *in)
{
	int	i;

	i = 0;
	while (i < in->nb_philo)
	{
		in->philo[i].id = i + 1;
		in->philo[i].last_eat = 0;
		in->philo[i].nb_meal = 0;
		in->philo[i].start = ft_get_time();
		in->philo[i].last_eat = ft_get_time();
		in->philo[i].print = &in->print;
		in->philo[i].left_fork = &in->forks[i];
		in->philo[i].right_fork = &in->forks[(i + 1) % in->nb_philo];
		in->philo[i].in = in;
		if (pthread_create(&in->philo[i].thread, NULL, ft_routine,
				&in->philo[i]) != 0)
		{
			while (i >= 0)
				pthread_detach(in->philo[i--].thread);
			return (0);
		}
		usleep(50);
		i++;
	}
	return (1);
}

int	ft_init(t_in *in)
{
	int	i;

	i = 0;
	in->philo = malloc(sizeof(t_philo) * in->nb_philo);
	if (!in->philo)
		return (0);
	in->forks = malloc(sizeof(pthread_mutex_t) * in->nb_philo);
	if (!in->forks)
	{
		free(in->philo);
		return (0);
	}
	while (i < in->nb_philo)
	{
		pthread_mutex_init(&in->forks[i], NULL);
		pthread_mutex_init(&in->philo[i].mut_eat, NULL);
		i++;
	}
	pthread_mutex_init(&in->print, NULL);
	in->dead = 0;
	in->finish = 0;
	return (1);
}
