/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:13:36 by daalmeid          #+#    #+#             */
/*   Updated: 2022/03/11 15:49:24 by daalmeid         ###   ########.fr       */
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

typedef struct s_philos
{
	int				philos_nb;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eating_nb;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_pulse;
	pthread_mutex_t	start;
	struct timeval	tv;
	int				dead_or_full;
	long			*last_supper;
}	t_philos;
int		ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_perror(char *err_msg, int err_nbr, int fd);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		prep_list(int ac, char **av, t_philos *list, pthread_t **tid);
int		mutex_creation(t_philos *list, pthread_t *tid);
int		eating_routine(t_philos *list, int i, int *j);
int		think_routine(t_philos *list, int i);
int		take_forks(t_philos *list, int i);
int		sleep_routine(t_philos *list, int i);
int		ft_usleep(int time_to_sleep, t_philos *list);
void	doom_clock(t_philos *list, pthread_t *tid);
int		thread_creation(t_philos *list, pthread_t *tid);

#endif