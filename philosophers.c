/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:42:45 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/01 18:25:51 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *test_drive(void *param)
{
	int				i;
	int				j;
	t_philos		*list;
	struct timeval	time;

	list = (t_philos *) param;
	i = list->DOA;
	j = 0;
	while (list->DOA != -1)
	{
		gettimeofday(&time, NULL);
		if (j != 0 && list->DOA != -1)	
			printf(".%ld: Philosopher%d is thinking.\n", (time.tv_sec - list->tv.tv_sec) * 1000 + time.tv_usec / 1000 - list->tv.tv_usec / 1000, i + 1);
		if (list->DOA != -1)
		{
			pthread_mutex_lock(&list->forks[i % list->philos_nb]);
			pthread_mutex_lock(&list->forks[(i + 1) % list->philos_nb]);
		}
		gettimeofday(&time, NULL);
		if (list->DOA != -1)
		{
			list->last_supper[i] = 0;
			printf(".%ld: Philosopher%d is eating.\n", (time.tv_sec - list->tv.tv_sec) * 1000 + time.tv_usec / 1000 - list->tv.tv_usec / 1000, i + 1);
		}
		usleep(list->time_eat);
		list->last_supper[i] = 0;
		gettimeofday(&time, NULL);
		list->last_supper[i] = (time.tv_sec - list->tv.tv_sec) * 1000 + time.tv_usec / 1000 - list->tv.tv_usec / 1000;
		if (++j == list->eating_nb)
		{
			printf(".%d: Philosopher%d finished eating.\n", list->last_supper[i], i + 1);
			list->last_supper[i] = 0;
			list->DOA--;
			if (list->DOA == 0)
			{
				list->DOA--;
				return (NULL);
			}
		}
		else if (list->DOA != -1)
			printf(".%d: Philosopher%d is sleeping.\n",list->last_supper[i], i + 1);
		pthread_mutex_unlock(&list->forks[i % list->philos_nb]);
		pthread_mutex_unlock(&list->forks[(i + 1) % list->philos_nb]);
		usleep(list->time_sleep);
		gettimeofday(&time, NULL);
	}
	return (NULL);
}

int	prep_list(int ac,  char **av, t_philos *list, pthread_t **tid)
{
	list->philos_nb = ft_atoi(av[1]);
	list->time_die = ft_atoi(av[2]);
	list->time_eat = ft_atoi(av[3]) * 1000;
	list->time_sleep = ft_atoi(av[4]) * 1000;
	list->eating_nb = -1;
	if (ac == 6)
		list->eating_nb = ft_atoi(av[5]);
	list->DOA = 0;
	list->forks = malloc(sizeof(pthread_mutex_t) * list->philos_nb);
	if (!list->forks)
		return (0);
	*tid = malloc(sizeof(pthread_t) * list->philos_nb);
	if (!*tid)
	{	
		free(list->forks);
		return (0);
	}
	list->last_supper = malloc(sizeof(int) * list->philos_nb);
	if (!list->last_supper)
	{	
		free(list->forks);
		free(*tid);
		return (0);
	}
	return (1);
}

int	dead_or_full(t_philos *list, pthread_t **tid)
{
	int				i;
	int				err;
	struct timeval	time;
	
	while (1)
	{
		i = 0;
		while (i < list->philos_nb)
		{
			gettimeofday(&time, NULL);
			if (list->DOA == -1)
			{
				printf("everyone ate.\n");
				break ;
				
			}
			else if (list->last_supper[i] != 0
					&& list->last_supper[i] + list->time_die <= (time.tv_sec - list->tv.tv_sec) * 1000 + time.tv_usec / 1000 - list->tv.tv_usec / 1000)
			{
				printf(".%ld: Philosopher%d died.\n", (time.tv_sec - list->tv.tv_sec) * 1000 + time.tv_usec / 1000 - list->tv.tv_usec / 1000, i + 1);
				list->DOA = -1;
				break ;
			}
			i++;
			if (i == list->philos_nb)
				i = 0;
		}
		i = 0;
		while(i < list->philos_nb)
		{
			pthread_mutex_unlock(&list->forks[i]);
			pthread_mutex_destroy(&list->forks[i++]);
		}
		i = 0;
		while (i < list->philos_nb)
		{
			err = pthread_join(tid[0][i], NULL);
			if (err != 0)
			{
				printf("Unable to join thread: error %d\n", err);
				return (0);
			}
				i++;
		}
		free (list->forks);
		free (*tid);
		free (list->last_supper);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	int				i;
	int				err;
	pthread_t		*tid = NULL;
	t_philos		list;

	if (ac != 5 && ac != 6)
		return (0);
	if (!prep_list(ac, av, &list, &tid))
		return (0);
	i = 0;
	while (i < list.philos_nb)
		pthread_mutex_init(&list.forks[i++], NULL);
	i = 0;
	gettimeofday(&list.tv, NULL);
	while(i < list.philos_nb)
	{
		err = pthread_create(&tid[i], NULL, &test_drive, (void *) &list);
		if (err != 0)
		{
			printf("Unable to create thread: error %d\n", err);
			return (0);
		}
		i++;
		usleep(20);
		list.DOA++;
	}
	if (!dead_or_full(&list, &tid))
	{	
		printf("End of program.\n");
		return (0);
	}
	return (0);
}
