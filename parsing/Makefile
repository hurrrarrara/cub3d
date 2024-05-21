# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 16:34:04 by rjacq             #+#    #+#              #
#    Updated: 2024/05/21 14:26:25 by rjacq            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS := parsing check_file check_line get_tex get_map get_color
OBJS = $(SRCS:%=%.o)
FLAGS = -Wall -Wextra -Werror
INCS = parsing.h ../libft/libft.h
NAME = parsing

all: $(NAME)

$(NAME): $(OBJS)
	make -C ../libft all bonus
	cc $(OBJS) -o $(NAME) ../libft/libft.a -g3

%.o: %.c $(INCS) Makefile
	cc $(FLAGS) -o $@ -c $< -I. -g3

.PHONY: all clean fclean re bonus

clean:
	make -C ../libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ../libft fclean
	rm -f $(NAME)

re: fclean all
