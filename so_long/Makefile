# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 17:42:31 by jeetienn          #+#    #+#              #
#    Updated: 2025/03/27 17:42:34 by jeetienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilib/minilibx_linux -Ilib/libft
LDFLAGS = -Llib/minilibx_linux -lmlx -Llib/libft -lft -lXext -lX11
SRCS = main.c errors.c load_map.c map_line.c key_press.c update_map.c count_items_and_checkings.c valid_map.c draw_map.c
OBJS = $(SRCS:.c=.o)
LIB_MLX = lib/minilibx_linux/libmlx.a
LIB_FT = lib/libft/libft.a

all: $(NAME)

$(NAME): $(LIB_FT) $(LIB_MLX) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIB_MLX):
	make -C lib/minilibx_linux

$(LIB_FT):
	make -C lib/libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C lib/minilibx_linux clean
	make -C lib/libft clean

fclean: clean
	rm -f $(NAME)
	make -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re