/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 21:57:46 by brminner          #+#    #+#             */
/*   Updated: 2023/07/31 22:02:13 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atol(char *str)
{
	int		i;
	long long	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb);
}
