/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:56:31 by brminner          #+#    #+#             */
/*   Updated: 2023/08/03 18:45:42 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error_handling(int argc, char **argv)
{
	int	i;

	i = 1;
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
		if (ft_atol(argv[i]) > 2147483647 || ft_atol(argv[i]) < 0)
		{
			printf("Error: argument too big\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_parsing(int argc, char **argv, t_input *input)
{
	input->nb_philo = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		input->nb_eat = ft_atoi(argv[5]);
	else
		input->nb_eat = -1;
}
