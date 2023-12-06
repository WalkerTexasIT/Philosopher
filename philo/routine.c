/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:36:26 by brminner          #+#    #+#             */
/*   Updated: 2023/12/06 16:36:29 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take_forks(t_philo *philo)
{
	if (philo->in->nb_philo == 1)
	{
		ft_print(philo, "has taken a fork");
		ft_usleep(philo->in->time_die, philo->in);
		ft_print(philo, "died");
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	if (ft_check_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->in->time_to_sleep, philo->in);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mut_eat);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(philo->mut_eat);
	ft_print(philo, "is eating");
	ft_usleep(philo->in->time_to_eat, philo->in);
	pthread_mutex_lock(philo->mut_eat);
	philo->nb_meal++;
	pthread_mutex_unlock(philo->mut_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_check_dead(philo))
			return (NULL);
		if (ft_take_forks(philo))
			return (NULL);
		ft_eat(philo);
		if (ft_check_dead(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (ft_check_dead(philo))
			return (NULL);
		ft_print(philo, "is thinking");
		if (philo->nb_meal == philo->in->nb_eat)
			return (NULL);
	}
	return (NULL);
}
