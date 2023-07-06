/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:49:06 by brminner          #+#    #+#             */
/*   Updated: 2023/07/06 14:56:55 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_philo *philo)
{
	
}

int main(int argc, char **argv)
{
	t_philo	philo;

	if (ft_error_handling(argc, argv) == 0)
		return (0);
	if (ft_parsing(argc, argv, &philo) == 0)
		return (0);
	if (ft_init(&philo) == 0)
		return (0);
}
