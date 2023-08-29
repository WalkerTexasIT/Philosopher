/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:37:32 by brminner          #+#    #+#             */
/*   Updated: 2023/08/29 23:25:28 by brminner         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->mut_eat);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->mut_eat);
	ft_print(philo, "is eating");
	ft_usleep(philo->input->time_to_eat);
	pthread_mutex_lock(&philo->mut_eat);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->mut_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->input->time_to_sleep);
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
		ft_print(philo, "is thinking");
		if (philo->input->nb_eat != -1 && philo->nb_meal == philo->input->nb_eat)
			return (NULL);
	}
	return (NULL);
}
