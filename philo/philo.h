/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:16:33 by brminner          #+#    #+#             */
/*   Updated: 2023/09/27 13:45:47 by brminner         ###   ########.fr       */
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
	pthread_mutex_t	*mut_dead;
	pthread_mutex_t	*mut_eat;
	struct s_in		*in;
	pthread_t		thread;
}				t_philo;

typedef struct s_in {
	int				nb_philo;
	int				time_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*muts_eat;
	pthread_mutex_t	print;
	pthread_t		check;
	pthread_mutex_t	mut_dead;
	int				dead;
	int				finish;
}				t_in;

int				ft_error_handling(int argc, char **argv);
int				ft_isdigit(char *str);
int				ft_atoi(char *str);
int				ft_strlen(char *str);
long long		ft_atol(char *str);
void			ft_parsing(int argc, char **argv, t_in *philo);
void			*ft_routine(void *arg);
long long int	ft_get_time(void);
void			ft_usleep(long long int time, t_in *in);
void			ft_print(t_philo *philo, char *str);
int				ft_exit(t_in *in);
int				ft_detach_threads(t_in *in);
int				ft_join_threads(t_in *in);
int				ft_init(t_in *in);
int				ft_create_threads(t_in *in);
int				ft_check_dead(t_philo *philo);
int				ft_strcmp(char *s1, char *s2);

#endif