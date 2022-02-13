# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 16:17:45 by min-jo            #+#    #+#              #
#    Updated: 2022/02/18 17:58:51 by min-jo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	fractol
SRC			:=	main.c\
				run.c\
				color.c\
				input.c\
				print.c
OBJ			:=	$(SRC:.c=.o)
LIB_DIR		:=	minilibx_opengl_20191021

CC			:=	gcc
CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+= -I$(LIB_DIR)
#CPPFLAGS	+= -I/usr/local/include

all:		$(NAME)

%.o:		%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -O2 $< -c -o $@

$(NAME):	$(OBJ)
	@make -C $(LIB_DIR) 2> /dev/null
#	$(CC) $(CFLAGS) $(CPPFLAGS) -O3 $^ -o $@ -L/usr/local/lib/ -lmlx -framework OpenGL -framework Appkit
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ -L$(LIB_DIR) -lmlx -framework OpenGL -framework Appkit

bonus:		$(NAME)

clean:
	make clean -C minilibx_opengl_20191021
	rm -f $(OBJ)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
