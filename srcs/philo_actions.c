/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:28:40 by daalmeid          #+#    #+#             */
/*   Updated: 2022/05/03 15:52:52 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

int	take_forks(t_philos *list, int i)
{
	int				sim_time;
	int				loop;
	struct timeval	time;

	loop = 0;
	while (loop < 2)
	{
		pthread_mutex_lock(&list->forks[(i + loop++) % list->philos_nb]);
		pthread_mutex_lock(&list->check_pulse);
		if (list->dead_or_full == -1)
		{	
			pthread_mutex_unlock(&list->check_pulse);
			return (-1);
		}
		pthread_mutex_unlock(&list->check_pulse);
		gettimeofday(&time, NULL);
		sim_time = (time.tv_sec - list->tv.tv_sec) * 1000000
			+ time.tv_usec - list->tv.tv_usec;
		printf("%d %d has taken a fork\n", sim_time / 1000, i + 1);
	}
	return (0);
}

int	think_routine(t_philos *list, int i)
{
	int				sim_time;
	struct timeval	time;

	pthread_mutex_lock(&list->check_pulse);
	if (list->dead_or_full == -1)
	{	
		pthread_mutex_unlock(&list->check_pulse);
		return (-1);
	}
	pthread_mutex_unlock(&list->check_pulse);
	gettimeofday(&time, NULL);
	sim_time = (time.tv_sec - list->tv.tv_sec) * 1000000
		+ time.tv_usec - list->tv.tv_usec;
	printf("%d %d is thinking\n", sim_time / 1000, i + 1);
	return (0);
}

static int	last_meal(t_philos *list, int i, struct timeval time)
{
	list->dead_or_full--;
	gettimeofday(&time, NULL);
	printf("%ld %d finished eating\n", ((time.tv_sec - list->tv.tv_sec)
			* 1000000 + time.tv_usec - list->tv.tv_usec) / 1000, i + 1);
	if (list->dead_or_full == 0)
	{
		list->dead_or_full--;
		pthread_mutex_unlock(&list->check_pulse);
		return (-1);
	}
	pthread_mutex_unlock(&list->check_pulse);
	return (0);
}

int	eating_routine(t_philos *list, int i, int *j)
{
	struct timeval	time;

	pthread_mutex_lock(&list->check_pulse);
	if (list->dead_or_full == -1)
	{	
		pthread_mutex_unlock(&list->check_pulse);
		return (-1);
	}
	gettimeofday(&time, NULL);
	list->last_supper[i] = (time.tv_sec - list->tv.tv_sec) * 1000000
		+ time.tv_usec - list->tv.tv_usec;
	printf("%ld %d is eating\n", list->last_supper[i] / 1000, i + 1);
	pthread_mutex_unlock(&list->check_pulse);
	if (ft_usleep(list->time_eat, list) == -1)
		return (-1);
	if (++*j == list->eating_nb)
	{
		pthread_mutex_lock(&list->check_pulse);
		if (last_meal(list, i, time) == -1)
			return (-1);
	}
	return (0);
}

int	sleep_routine(t_philos *list, int i)
{
	int				sim_time;
	struct timeval	time;

	pthread_mutex_lock(&list->check_pulse);
	if (list->dead_or_full == -1)
	{	
		pthread_mutex_unlock(&list->check_pulse);
		return (-1);
	}
	pthread_mutex_unlock(&list->check_pulse);
	gettimeofday(&time, NULL);
	sim_time = (time.tv_sec - list->tv.tv_sec) * 1000000
		+ time.tv_usec - list->tv.tv_usec;
	printf("%d %d is sleeping\n", sim_time / 1000, i + 1);
	pthread_mutex_unlock(&list->forks[i % list->philos_nb]);
	pthread_mutex_unlock(&list->forks[(i + 1) % list->philos_nb]);
	if (ft_usleep(list->time_sleep, list) == -1)
		return (-1);
	return (0);
}
