/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:09:05 by brminner          #+#    #+#             */
/*   Updated: 2023/09/27 14:26:47 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->in->mut_dead);
	if (philo->in->dead == 1)
	{
		pthread_mutex_unlock(&philo->in->mut_dead);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->in->mut_dead);
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
	return (0);
}

int	ft_create_threads(t_in *in)
{
	int	i;

	i = -1;
	while (++i < in->nb_philo)
	{
		in->philo[i].id = i + 1;
		in->philo[i].last_eat = 0;
		in->philo[i].nb_meal = 0;
		in->philo[i].start = ft_get_time();
		in->philo[i].last_eat = ft_get_time();
		in->philo[i].print = &in->print;
		in->philo[i].mut_eat = &in->muts_eat[i];
		in->philo[i].left_fork = &in->forks[i];
		in->philo[i].right_fork = &in->forks[(i + 1) % in->nb_philo];
		in->philo[i].mut_dead = &in->mut_dead;
		in->philo[i].in = in;
		if (pthread_create(&in->philo[i].thread, NULL, ft_routine,
				&in->philo[i]) != 0)
		{
			printf("Error creating thread\n");
			return (0);
		}
		usleep(100);
	}
	return (1);
}

int	malloc_vars(t_in *in)
{
	in->philo = malloc(sizeof(t_philo) * in->nb_philo);
	if (!in->philo)
		return (0);
	in->forks = malloc(sizeof(pthread_mutex_t) * in->nb_philo);
	if (!in->forks)
	{
		free(in->philo);
		in->philo = NULL;
		return (0);
	}
	in->muts_eat = malloc(sizeof(pthread_mutex_t) * in->nb_philo);
	if (!in->muts_eat)
	{
		free(in->philo);
		in->philo = NULL;
		free(in->forks);
		in->forks = NULL;
		return (0);
	}
	return (1);
}

int	ft_init(t_in *in)
{
	int	i;

	i = 0;
	if (malloc_vars(in) == 0)
		return (0);
	while (i < in->nb_philo)
	{
		pthread_mutex_init(&in->forks[i], NULL);
		pthread_mutex_init(&in->muts_eat[i], NULL);
		i++;
	}
	pthread_mutex_init(&in->print, NULL);
	pthread_mutex_init(&in->mut_dead, NULL);
	in->dead = 0;
	in->finish = 0;
	return (1);
}
