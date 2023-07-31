/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:16:33 by brminner          #+#    #+#             */
/*   Updated: 2023/07/31 22:28:33 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	struct s_input	*input;
}				t_philo;

typedef struct s_input {
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_input;

int		ft_error_handling(int argc, char **argv);
int		ft_isdigit(char *str);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
long long ft_atol(char *str);

#endif