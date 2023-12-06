/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:56:31 by brminner          #+#    #+#             */
/*   Updated: 2023/09/05 15:55:48 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	if (ft_check_dead(philo) == 1)
		return ;
	if (ft_strcmp(str, "died") == 0)
	{
		pthread_mutex_lock(&philo->in->mut_dead);
		philo->in->dead = 1;
		pthread_mutex_unlock(&philo->in->mut_dead);
		pthread_mutex_lock(philo->print);
		printf("%lld %d %s\n", ft_get_time() - philo->start, philo->id, str);
		return ;
	}
	pthread_mutex_lock(philo->print);
	printf("%lld %d %s\n", ft_get_time() - philo->start, philo->id, str);
	pthread_mutex_unlock(philo->print);
}

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
		if (ft_atol(argv[i]) > 2147483647 || ft_atol(argv[i]) <= 0)
		{
			printf("Error: wrong argument\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_parsing(int argc, char **argv, t_in *in)
{
	in->nb_philo = ft_atoi(argv[1]);
	in->time_die = ft_atoi(argv[2]);
	in->time_to_eat = ft_atoi(argv[3]);
	in->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		in->nb_eat = ft_atoi(argv[5]);
	else
		in->nb_eat = -1;
}
