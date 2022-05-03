/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:16:52 by daalmeid          #+#    #+#             */
/*   Updated: 2022/05/03 16:03:33 by daalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	ft_perror(char *err_msg, int err_nbr, int fd)
{
	ft_putstr_fd(err_msg, fd);
	ft_putnbr_fd(err_nbr, fd);
	ft_putchar_fd('\n', fd);
}
