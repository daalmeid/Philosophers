/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:02:22 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/14 13:28:46 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	full_routine(t_philos *list, int thread_nbr)
{
	int	j;

	j = 0;
	if (j == 0 && thread_nbr % 2 != 0)
		usleep(3000);
	while (1)
	{
		if (j != 0 && think_routine(list, thread_nbr) == -1)
			break ;
		if (take_forks(list, thread_nbr) == -1)
			break ;
		if (eating_routine(list, thread_nbr, &j) == -1)
			break ;
		if (sleep_routine(list, thread_nbr) == -1)
			break ;
	}
	pthread_mutex_unlock(&list->forks[thread_nbr % list->philos_nb]);
	pthread_mutex_unlock(&list->forks[(thread_nbr + 1) % list->philos_nb]);
}

static void	*starting_line(void *param)
{
	static int		i = 0;
	int				thread_nbr;
	t_philos		*list;

	list = (t_philos *) param;
	pthread_mutex_lock(&list->check_pulse);
	thread_nbr = i++;
	pthread_mutex_unlock(&list->check_pulse);
	pthread_mutex_lock(&list->start);
	pthread_mutex_unlock(&list->start);
	full_routine(list, thread_nbr);
	return (NULL);
}

int	thread_creation(t_philos *list, pthread_t *tid)
{
	int	i;
	int	err;

	i = 0;
	pthread_mutex_lock(&list->start);
	while (i < list->philos_nb)
	{
		err = pthread_create(&tid[i], NULL, &starting_line, (void *) list);
		if (err != 0)
		{
			printf("Unable to create thread: error %d\n", err);
			free (list->forks);
			free (tid);
			free (list->last_supper);
			return (0);
		}
		i++;
	}
	gettimeofday(&list->tv, NULL);
	pthread_mutex_unlock(&list->start);
	return (1);
}
