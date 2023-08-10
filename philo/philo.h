/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:16:33 by brminner          #+#    #+#             */
/*   Updated: 2023/08/10 17:24:52 by brminner         ###   ########.fr       */
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
	long long int	last_eat;
	int				nb_meal;
	long long int	start;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
	struct s_input	*input;
	pthread_t		thread;
}				t_philo;

typedef struct s_input {
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_t		check;
	int				dead;
	int				finish;
}				t_input;

int				ft_error_handling(int argc, char **argv);
int				ft_isdigit(char *str);
int				ft_atoi(char *str);
int				ft_strlen(char *str);
long long		ft_atol(char *str);
void			ft_parsing(int argc, char **argv, t_input *philo);
void			*ft_routine(void *arg);
long long int	ft_get_time(void);
void 			ft_usleep(long long int time);
void			ft_print(t_philo *philo, char *str);

#endif