# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daalmeid <daalmeid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 15:12:54 by daalmeid          #+#    #+#              #
#    Updated: 2022/03/01 15:17:44 by daalmeid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers

SRCS	= philosophers.c ft_atoi.c

OBJS	= *.o

RM = rm -f

$(NAME): $(OBJS)
	gcc -Wextra -Wall -Werror -pthread $(OBJS) -o $(NAME)

$(OBJS):
	gcc -Wall -Wextra -Werror -c $(SRCS)
	
all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

bonus: clean
	gcc -Wall -Wextra -Werror -c $(SRCS_BONUS)
	ar rc $(NAME) $(OBJS)
