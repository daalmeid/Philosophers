/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:13:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/01 15:21:13 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philos
{
	int				DOA;
	pthread_mutex_t	*forks;
	struct timeval	tv;
	int				philos_nb;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eating_nb;
	int				*last_supper;
}t_philos;
int	ft_atoi(const char *str);

#endif