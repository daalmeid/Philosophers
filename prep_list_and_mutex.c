/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_list_and_mutex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:25:41 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/10 14:17:08 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	prep_list(int ac, char **av, t_philos *list, pthread_t **tid)
{
	list->philos_nb = ft_atoi(av[1]);
	list->time_die = ft_atoi(av[2]);
	list->time_eat = ft_atoi(av[3]);
	list->time_sleep = ft_atoi(av[4]);
	list->eating_nb = -1;
	if (ac == 6)
		list->eating_nb = ft_atoi(av[5]);
	list->dead_or_full = list->philos_nb;
	list->forks = malloc(sizeof(pthread_mutex_t) * list->philos_nb);
	if (!list->forks)
		return (0);
	*tid = malloc(sizeof(pthread_t) * list->philos_nb);
	if (!*tid)
	{	
		free(list->forks);
		return (0);
	}
	list->last_supper = malloc(sizeof(long) * list->philos_nb);
	if (!list->last_supper)
	{	
		free(list->forks);
		free(*tid);
		return (0);
	}
	return (1);
}

int	start_and_death_mutex(t_philos *list, pthread_t *tid, int err)
{
	err = pthread_mutex_init(&list->check_pulse, NULL);
	if (err != 0)
	{
		ft_perror("Mutex_init failed: error ", err, 2);
		free (list->forks);
		free (tid);
		free (list->last_supper);
		return (0);
	}
	err = pthread_mutex_init(&list->start, NULL);
	if (err != 0)
	{
		ft_perror("Mutex_init failed: error ", err, 2);
		free (list->forks);
		free (tid);
		free (list->last_supper);
		return (0);
	}
	return (1);
}

int	mutex_creation(t_philos *list, pthread_t *tid)
{
	int	i;
	int	err;

	i = 0;
	while (i < list->philos_nb)
	{
		err = pthread_mutex_init(&list->forks[i++], NULL);
		if (err != 0)
		{
			ft_perror("Mutex_init failed: error ", err, 2);
			free (list->forks);
			free (tid);
			free (list->last_supper);
			return (0);
		}
	}
	if (start_and_death_mutex(list, tid, err) == 0)
		return (0);
	return (1);
}
