# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 16:48:15 by daalmeid          #+#    #+#              #
#    Updated: 2022/05/03 16:04:59 by daalmeid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################## Program #################

NAME =			philo

################## COLORS ##################

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################## TERMINAL ################

RM		=		rm -f

################## COMPILER ################

CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra

################## FILES ###################

SRCS	=		srcs/main.c\
				srcs/ft_atoi.c\
				srcs/ft_putchar_fd.c\
				srcs/ft_putstr_fd.c\
				srcs/doom_clock.c\
				srcs/philo_actions.c\
				srcs/prep_list_and_mutex.c\
				srcs/ft_isdigit.c\
				srcs/ft_strlen.c\
				srcs/ft_strncmp.c\
				srcs/threads.c\
				srcs/ft_putnbr_fd.c\
				srcs/ft_perror.c\
				srcs/ft_usleep.c

OBJS	=		$(SRCS:.c=.o)	

################## RULES ###################

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)

################## CLEAN ###################

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re