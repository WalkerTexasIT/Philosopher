/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:49:55 by brminner          #+#    #+#             */
/*   Updated: 2023/07/06 13:23:14 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_handling(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
		{
			printf("Error: wrong argument\n");
			return (0);
		}
		if (ft_atol(argv[i]) > 2147483647)
		{
			printf("Error: argument too big\n");
			return (0);
		}
		i++;
	}
}

int	ft_parsing(int argc, char **argv, t_philo *philo)
{
	philo->input.nb_philo = ft_atoi(argv[1]);
	philo->input.time_to_die = ft_atoi(argv[2]);
	philo->input.time_to_eat = ft_atoi(argv[3]);
	philo->input.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->input.nb_eat = ft_atoi(argv[5]);
	else
		philo->input.nb_eat = -1;
}
