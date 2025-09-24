# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 20:30:57 by jeetienn          #+#    #+#              #
#    Updated: 2025/02/21 18:20:24 by jeetienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	src/ft_isalnum.c src/ft_isprint.c src/ft_memcmp.c src/ft_putchar_fd.c src/ft_split.c \
				src/ft_strlcat.c src/ft_strncmp.c src/ft_substr.c src/ft_atoi.c src/ft_isalpha.c \
				src/ft_itoa.c src/ft_memcpy.c src/ft_putendl_fd.c src/ft_strchr.c src/ft_strlcpy.c \
				src/ft_strnstr.c src/ft_tolower.c src/ft_bzero.c src/ft_isascii.c \
				src/ft_memmove.c src/ft_putnbr_fd.c src/ft_strdup.c src/ft_strlen.c src/ft_strrchr.c \
				src/ft_toupper.c src/ft_calloc.c src/ft_isdigit.c src/ft_memchr.c src/ft_memset.c \
				src/ft_putstr_fd.c src/ft_strjoin.c src/ft_strmapi.c src/ft_strtrim.c src/ft_striteri.c \
				src/ft_print_f/ft_printf.c \
				src/ft_print_f/ft_print_hex.c src/ft_print_f/ft_print_nbr.c src/ft_print_f/ft_print_ptr.c \
				src/ft_print_f/ft_print_u.c src/ft_print_f/ft_print_utils.c \
		

OBJS		=	$(SRCS:.c=.o)

CC			=	cc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror

NAME		=	libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
