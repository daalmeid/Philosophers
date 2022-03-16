/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_clock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:21:40 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/11 14:43:44 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	mutex_destroyer(t_philos *list, int i, int err)
{
	i = 0;
	while (i < list->philos_nb)
	{
		err = pthread_mutex_destroy(&list->forks[i++]);
		if (err != 0)
		{
			printf("Unable to destroy mutex: error %d\n", err);
			return ;
		}
	}
	err = pthread_mutex_destroy(&list->check_pulse);
	if (err != 0)
	{
		printf("Unable to destroy mutex: error %d\n", err);
		return ;
	}
	err = pthread_mutex_destroy(&list->start);
	if (err != 0)
	{
		printf("Unable to destroy mutex: error %d\n", err);
		return ;
	}
}

static void	cleanup(t_philos *list, pthread_t *tid)
{
	int	i;
	int	err;

	i = 0;
	while (i < list->philos_nb)
	{
		err = pthread_join(tid[i], NULL);
		if (err != 0)
		{
			printf("Unable to join thread: error %d\n", err);
			return ;
		}
			i++;
	}
	mutex_destroyer(list, i, err);
}

static void	print_death(t_philos *list, struct timeval time, long s_time, int i)
{
	list->dead_or_full = -1;
	gettimeofday(&time, NULL);
	s_time = (time.tv_sec - list->tv.tv_sec) * 1000000 + time.tv_usec
		- list->tv.tv_usec;
	printf("%ld %d died\n", s_time / 1000, i + 1);
	pthread_mutex_unlock(&list->forks[i % list->philos_nb]);
}

void	doom_clock(t_philos *list, pthread_t *tid)
{
	int				i;
	long			sim_time;
	struct timeval	time;

	i = 0;
	while (1)
	{
		gettimeofday(&time, NULL);
		sim_time = (time.tv_sec - list->tv.tv_sec) * 1000000 + time.tv_usec
			- list->tv.tv_usec;
		pthread_mutex_lock(&list->check_pulse);
		if (list->last_supper[i] + list->time_die * 1000 <= sim_time)
			print_death(list, time, sim_time, i);
		if (list->dead_or_full == -1)
			break ;
		pthread_mutex_unlock(&list->check_pulse);
		if (++i == list->philos_nb)
			i = 0;
	}
	pthread_mutex_unlock(&list->check_pulse);
	cleanup(list, tid);
}
