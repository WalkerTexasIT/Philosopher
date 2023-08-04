/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:37:32 by brminner          #+#    #+#             */
/*   Updated: 2023/08/03 19:08:50 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
}

void	ft_eat(t_philo *philo)
{
	ft_print(philo, "is eating");
	philo->last_eat = ft_get_time();
	ft_usleep(philo->input->time_to_eat);
	philo->nb_meal++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->input->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		if (philo->input->nb_eat != -1 && philo->nb_meal == philo->input->nb_eat)
			return (NULL);
		if (philo->input->dead == 1)
			return (NULL);
	}
	return (NULL);
}