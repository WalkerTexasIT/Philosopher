/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:09:05 by brminner          #+#    #+#             */
/*   Updated: 2023/09/13 15:34:46 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	n;

	n = 0;
	while (s1[n] == s2[n] && s1[n] != 0 && s2[n] != 0)
		n++;
	return (s1[n] - s2[n]);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->in->mut_dead);
	if (philo->in->dead == 1)
	{
		pthread_mutex_unlock(&philo->in->mut_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->in->mut_dead);
	if (ft_strcmp(str, "died") == 0)
	{
		pthread_mutex_lock(&philo->in->mut_dead);
		philo->in->dead = 1;
		pthread_mutex_unlock(&philo->in->mut_dead);
		pthread_mutex_lock(philo->print);
		printf("%lld %d %s\n", ft_get_time() - philo->start, philo->id, str);
		return ;
	}
	printf("%lld %d %s\n", ft_get_time() - philo->start, philo->id, str);
	pthread_mutex_unlock(philo->print);
}

int	ft_detach_threads(t_in *in)
{
	int	i;

	i = 0;
	while (i < in->nb_philo)
	{
		printf("%d lol\n", pthread_detach(in->philo[i].thread));
			//return (0);
		i++;
	}
	//ft_join_threads(in);
	printf("All threads detached\n");
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

	i = -1;
	while (++i < in->nb_philo)
	{
		in->philo[i].id = i + 1;
		in->philo[i].last_eat = 0;
		in->philo[i].nb_meal = 0;
		in->philo[i].start = ft_get_time();
		in->philo[i].last_eat = ft_get_time();
		in->philo[i].print = &in->print;
		in->philo[i].left_fork = &in->forks[i];
		in->philo[i].right_fork = &in->forks[(i + 1) % in->nb_philo];
		in->philo[i].mut_dead = &in->mut_dead;
		in->philo[i].in = in;
		if (pthread_create(&in->philo[i].thread, NULL, ft_routine,
				&in->philo[i]) != 0)
		{
			while (i >= 0)
				pthread_detach(in->philo[i--].thread);
			return (0);
		}
		usleep(100);
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
	pthread_mutex_init(&in->mut_dead, NULL);
	in->dead = 0;
	in->finish = 0;
	return (1);
}
