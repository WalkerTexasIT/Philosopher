/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:53:17 by brminner          #+#    #+#             */
/*   Updated: 2023/07/06 12:45:38 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	t_input			input;
}				t_philo;

typedef struct s_input {
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
}				t_input;
}



int		ft_error_handling(int argc, char **argv);
int		ft_isdigit(char *str);
int		ft_atoi(char *str);


#endif