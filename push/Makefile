NAME = push_swap
LIBFTNAME = libft.a
LIBFTDIR = ./libft
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRCS = push_swap.c init_a_to_b.c init_b_to_a.c push.c \
		rev_rotate.c rotate.c sort_stacks.c sort_three.c \
		stack_init.c stack_utils.c swap.c errors.c free_split.c\
		
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFTDIR)/$(LIBFTNAME):
	@make -C $(LIBFTDIR)

$(NAME): $(OBJS) $(LIBFTDIR)/$(LIBFTNAME)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFTDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re