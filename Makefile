# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 15:12:54 by daalmeid          #+#    #+#              #
#    Updated: 2022/03/14 13:40:11 by daalmeid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= main.c ft_atoi.c ft_putchar_fd.c ft_putstr_fd.c doom_clock.c\
		  philo_actions.c prep_list_and_mutex.c ft_isdigit.c ft_strlen.c \
		  ft_strncmp.c threads.c ft_putnbr_fd.c ft_perror.c ft_usleep.c

OBJS	= *.o

RM 		= rm -f

FLAGS	= -Wextra -Wall -Werror

all:	$(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) -pthread $(OBJS) -o $(NAME)

$(OBJS):
	cc $(FLAGS) -pthread -c $(SRCS)
	
clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all
