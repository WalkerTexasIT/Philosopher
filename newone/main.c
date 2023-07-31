/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:55:33 by brminner          #+#    #+#             */
/*   Updated: 2023/07/31 22:16:18 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->input.nb_philo);
	if (!philo->forks)
		return (0);
	while (i < philo->input.nb_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->print, NULL);
	pthread_mutex_init(&philo->dead, NULL);
	return (1);
}

int main(int argc, char **argv)
{
	t_philo	philo;

	if (ft_error_handling(argc, argv) == 0)
		return (0);
	ft_parsing(argc, argv, &philo);
	ft_init(&philo);
	ft_create_threads(&philo);
	ft_join_threads(&philo);
	return (0);
}
