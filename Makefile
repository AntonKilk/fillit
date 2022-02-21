# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkivilah <nkivilah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 17:52:23 by nkivilah          #+#    #+#              #
#    Updated: 2022/02/16 21:15:21 by nkivilah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
SRCS = *.c
OBJS = *.o
HDR = fillit.h
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(NAME) $(SRCS) -I $(HDR) -L. libft/libft.a

clean:
	/bin/rm -f $(OBJS)
	make -C $(LIBFT) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all
