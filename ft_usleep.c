/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:35:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/11 15:49:22 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(int time_to_sleep, t_philos *list)
{
	long int		initial_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	initial_time = time.tv_sec * 1000000 + time.tv_usec;
	while (initial_time + time_to_sleep * 1000 > (time.tv_sec * 1000000
			+ time.tv_usec))
	{
		pthread_mutex_lock(&list->check_pulse);
		if (list->dead_or_full == -1)
		{	
			pthread_mutex_unlock(&list->check_pulse);
			return (-1);
		}
		pthread_mutex_unlock(&list->check_pulse);
		gettimeofday(&time, NULL);
	}
	return (0);
}
