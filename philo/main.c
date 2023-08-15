/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:55:33 by brminner          #+#    #+#             */
/*   Updated: 2023/08/15 13:12:21 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_detach_threads(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_detach(input->philo[i].thread) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_join_threads(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_join(input->philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check(t_input *input)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < input->nb_philo)
		{
			if (input->philo[i].last_eat != -1 && input->philo[i].nb_meal != input->nb_eat && ft_get_time() - input->philo[i].last_eat > input->time_to_die)
			{
				//printf("%d : last eat -> %lld\nnb of eat : %d\n", input->philo[i].id, input->philo[i].last_eat, input->philo[i].nb_meal);
				ft_print(&input->philo[i], "died");
				return (ft_detach_threads(input));
			}
			if (input->nb_eat != -1 && input->philo[i].nb_meal == input->nb_eat && input->philo[i].last_eat != -1)
			{
				input->philo[i].last_eat = -1;
				input->finish++;
			}
			if (input->finish == input->nb_philo - 1)
				return (ft_join_threads(input));
			i++;
		}
	}
	return (1);
}

int	ft_create_threads(t_input *input)
{
	int	i;

	i = 0;
	while (i < input->nb_philo)
	{
		input->philo[i].id = i + 1;
		input->philo[i].last_eat = 0;
		input->philo[i].nb_meal = 0;
		input->philo[i].start = ft_get_time();
		input->philo[i].last_eat = ft_get_time();
		input->philo[i].print = &input->print;
		input->philo[i].left_fork = &input->forks[i];
		input->philo[i].right_fork = &input->forks[(i + 1) % input->nb_philo];
		input->philo[i].input = input;
		if (pthread_create(&input->philo[i].thread, NULL, ft_routine,
				&input->philo[i]) != 0)
			return (0);
		usleep(20);
		i++;
	}
	return (1);
}

int	ft_init(t_input *input)
{
	int	i;

	i = 0;
	input->philo = malloc(sizeof(t_philo) * input->nb_philo);
	if (!input->philo)
		return (0);
	input->forks = malloc(sizeof(pthread_mutex_t) * input->nb_philo);
	if (!input->forks)
		return (0);
	while (i < input->nb_philo)
	{
		pthread_mutex_init(&input->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&input->print, NULL);
	input->dead = 0;
	input->finish = 0;
	return (1);
}

int main(int argc, char **argv)
{
	t_input	input;

	if (ft_error_handling(argc, argv) == 0)
		return (0);
	ft_parsing(argc, argv, &input);
	ft_init(&input);
	ft_create_threads(&input);
	ft_check(&input);
	free(input.philo);
	free(input.forks);
	return (0);
}
