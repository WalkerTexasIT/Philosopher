/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brminner <brminner@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:54:04 by brminner          #+#    #+#             */
/*   Updated: 2023/07/06 10:42:29 by brminner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct mutex_data {
	int data;
	pthread_mutex_t mutex;
}			mutex_data;

void	*ft_idk(void *arg)
{
	mutex_data *md = (mutex_data *)arg;
	pthread_mutex_lock(&md->mutex);
	md->data++;
	pthread_mutex_unlock(&md->mutex);
	printf("Hello from thread\n");
	pthread_exit(EXIT_SUCCESS);
	return (NULL);
}

int main(void)
{
	pthread_t treadh1;
	pthread_t treadh2;
	mutex_data md;

	md.data = 0;

	if (pthread_mutex_init(&md.mutex, NULL) != 0)
	{
		printf("Mutex init failed\n");
		return (1);
	}
	
	printf("Before thread\n");
	pthread_create(&treadh1, NULL, &ft_idk, &md);
	pthread_create(&treadh2, NULL, &ft_idk, &md);
	pthread_join(treadh1, NULL);
	pthread_join(treadh2, NULL);
	printf("Data after thread : %d\n", md.data);
	printf("After the creation of thread\n");
	return (0);
}