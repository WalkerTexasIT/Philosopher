/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:55:33 by brminner          #+#    #+#             */
/*   Updated: 2023/09/13 15:21:23 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit(t_in *in)
{
	int	i;

	i = 0;
	while (i < in->nb_philo)
	{
		pthread_mutex_destroy(&in->philo[i].mut_eat);
		pthread_mutex_destroy(&in->forks[i++]);
	}
	pthread_mutex_destroy(&in->mut_dead);
	pthread_mutex_destroy(&in->print);
	free(in->philo);
	free(in->forks);
	return (0);
}

int	sub_check(t_in *in, int i)
{
	pthread_mutex_lock(&in->philo[i].mut_eat);
	if (in->philo[i].last_eat != -1 && in->philo[i].nb_meal != in->nb_eat
		&& ft_get_time() - in->philo[i].last_eat > in->time_die)
	{
		ft_print(&in->philo[i], "died");
		pthread_mutex_lock(&in->mut_dead);
		in->dead = 1;
		pthread_mutex_unlock(&in->mut_dead);
		return (ft_detach_threads(in));
	}
	if (in->nb_eat != -1 && in->philo[i].nb_meal == in->nb_eat
		&& in->philo[i].last_eat != -1)
	{
		in->philo[i].last_eat = -1;
		in->finish++;
	}
	pthread_mutex_unlock(&in->philo[i].mut_eat);
	return (1);
}

int	ft_check(t_in *in)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < in->nb_philo)
		{
			if (sub_check(in, i) == 0)
				return (0);
			if (in->finish == in->nb_philo - 1)
				return (ft_join_threads(in));
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_in	in;

	if (ft_error_handling(argc, argv) == 0)
		return (0);
	ft_parsing(argc, argv, &in);
	if (ft_init(&in) == 0)
		return (0);
	if (ft_create_threads(&in) == 0)
		return (ft_exit(&in));
	ft_check(&in);
	ft_exit(&in);
	return (0);
}
