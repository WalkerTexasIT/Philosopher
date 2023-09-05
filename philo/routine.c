/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:37:32 by brminner          #+#    #+#             */
/*   Updated: 2023/09/05 10:47:00 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->in->mut_dead);
	if (philo->in->dead == 1)
		return (1);
	pthread_mutex_unlock(&philo->in->mut_dead);
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	if (philo->in->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->in->mut_dead);
		ft_usleep(philo->in->time_die);
		ft_print(philo, "died");
		philo->in->dead = 1;
		pthread_mutex_unlock(&philo->in->mut_dead);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	return (0);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_eat);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->mut_eat);
	ft_print(philo, "is eating");
	ft_usleep(philo->in->time_to_eat);
	pthread_mutex_lock(&philo->mut_eat);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->mut_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->in->time_to_sleep);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_take_forks(philo))
			return (NULL);
		pthread_mutex_lock(&philo->in->mut_dead);
		ft_eat(philo);
		ft_sleep(philo);
		pthread_mutex_lock(&philo->in->mut_dead);
		if (philo->in->dead == 1)
			return (NULL);
		pthread_mutex_unlock(&philo->in->mut_dead);
		ft_print(philo, "is thinking");
		if (philo->in->nb_eat != -1 && philo->nb_meal == philo->in->nb_eat)
			return (NULL);
	}
	return (NULL);
}
