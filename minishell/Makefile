NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/minishell.c src/minishell_utils.c \
src/parser.c src/parser_create.c src/parser_create2.c src/parser_handlers.c src/parser_utils.c src/parser_utils2.c\
src/execute.c src/execute_commands.c src/execute_pipeline_utils.c src/execute_pipeline.c \
src/execute_redirects.c src/execute_utils.c src/execute_utils2.c\
src/env.c src/env_utils.c src/env_utils2.c\
src/heredoc.c src/heredoc_utils.c \
src/errors.c src/errors2.c \
src/lexer.c src/lexer_utils.c src/lexer_utils2.c src/lexer_redirect.c src/lexer_quotes.c src/lexer_extract.c \
src/builtins/builtin_cd.c src/builtins/builtin_echo_env_pwd.c \
src/builtins/builtin_export.c src/builtins/builtin_export2.c src/builtins/builtin_export3.c \
src/builtins/builtin_unset_exit.c src/builtins/builtin_utils.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
LIBFT_DIR = libft
INC_DIR = inc

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re