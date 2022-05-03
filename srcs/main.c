/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:42:45 by daalmeid          #+#    #+#             */
/*   Updated: 2022/05/03 15:52:45 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

static int	error_management(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]) || j > 9)
			{
				ft_putstr_fd("Wrong input: unacceptable value as argument\n", 2);
				return (0);
			}
			j++;
		}
		if ((ft_strlen(av[i]) == 10 && ft_strncmp("2147483647", av[i], 11) < 0)
			|| ft_atoi(av[i]) == 0)
		{
			ft_putstr_fd("Wrong input: unacceptable value as argument\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	pthread_t		*tid;
	t_philos		list;
	int				i;

	i = 0;
	if (ac != 5 && ac != 6)
	{	
		ft_putstr_fd("Wrong argument input\n", 2);
		return (-1);
	}
	if (!error_management(ac, av))
		return (-1);
	if (!prep_list(ac, av, &list, &tid))
		return (-1);
	if (!mutex_creation(&list, tid))
		return (-1);
	while (i < list.philos_nb)
		list.last_supper[i++] = 0;
	if (!thread_creation(&list, tid))
		return (-1);
	doom_clock(&list, tid);
	free (list.forks);
	free (tid);
	free (list.last_supper);
	return (0);
}
