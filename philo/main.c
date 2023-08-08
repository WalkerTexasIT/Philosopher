/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:55:33 by brminner          #+#    #+#             */
/*   Updated: 2023/08/08 14:07:35 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_check(void *arg)
{
	t_input	*input;
	int		i;

	input = (t_input *)arg;
	while (1)
	{
		i = -1;
		while (++i < input->nb_philo)
		{
			if (ft_get_time() - input->philo[i].last_eat > input->time_to_die)
			{
				input->dead = 1;
				ft_print(&input->philo[i], "dieds");
				i = -1;
				while (++i < input->nb_philo)
					pthread_detach(input->philo[i].thread);
				return (NULL);
			}
		}
	}
	return (NULL);
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
		input->philo[i].print = &input->print;
		input->philo[i].left_fork = &input->forks[i];
		input->philo[i].right_fork = &input->forks[(i + 1) % input->nb_philo];
		input->philo[i].input = input;
		if (pthread_create(&input->philo[i].thread, NULL, ft_routine,
				&input->philo[i]) != 0)
			return (0);
		usleep(100);
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
	return (1);
}

int	ft_join_threads(t_input *input)
{
	int	i;

	i = 0;
	printf("test\n");
	while (i < input->nb_philo)
	{
		if (pthread_join(input->philo[i].thread, NULL) != 0)
			return (0);
		printf("thread %d joined\n", i);
		i++;
	}
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
	if (pthread_create(&input.check, NULL, ft_check, &input) != 0)
		return (0);
	// ft_check(&input);
	// input.dead = 1;
	// printf("%d\n", input.dead);
	ft_join_threads(&input);
	return (0);
}
