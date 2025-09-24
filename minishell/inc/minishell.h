/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:05:45 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/05 18:42:42 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include "libft.h"

extern int	g_signal;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_heredoc
{
	char				*delim;
	char				*content;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redirect
{
	char				*filename;
	int					append;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*redirect_in;
	t_redirect		*redirects_out;
	t_heredoc		*heredocs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_builtin
{
	char		*name;
	void		(*func)(t_cmd *cmd, t_env **env, int *exit_status);
}	t_builtin;

// to limit arguments in functions

typedef struct s_parse_context
{
	t_cmd	**head;
	t_cmd	**current_cmd;
	char	**args;
	int		*arg_index;
	int		*exit_status;
}	t_parse_context;

typedef struct s_export_context
{
	t_env	**env;
	int		*arg_index;
	int		*error_occurred;
	int		*exit_status;
}	t_export_context;

typedef struct s_env_creation_context
{
	char	*key;
	char	*value;
	int		*exit_status;
}	t_env_creation_context;

typedef struct s_lexer_context
{
	t_env	*env;
	int		*exit_status;
	int		*after_redirect;
}	t_lexer_context;

typedef struct s_pipeline_init_context
{
	t_cmd	*pipeline;
	t_env	*env;
	pid_t	*pids;
	int		cmd_count;
	int		*exit_status;
}	t_pipeline_init_context;

typedef struct s_token_list
{
	t_token	*tokens;
	t_token	*last;
}	t_token_list;

typedef struct s_cleanup_data
{
	char	*path;
	char	**envp;
	char	**args;
	t_env	*env;
	int		*exit_status;
}	t_cleanup_data;

// minishell.c minishell_utils.c
char			*format_prompt(t_env *env);
void			sigint_handler(int sig);

/* lexer_utils.c */
int				is_whitespace(char c);
int				is_operator(char *str, int i);
t_token			*create_token(t_token_type type, char *value);
void			free_tokens(t_token *tokens);
void			add_token(t_token **tokens, t_token **last, t_token *token);
int				is_redirect_token(t_token *token);
void			skip_whitespace(char *line, int *i);

/* lexer_extract.c */
char			*extract_env_variable(char *str,
					int *i, t_env *env, int *exit_status);
char			*extract_single_quoted(char *str, int *i);
char			*extract_plain_word(char *str, int *i);

/* lexer_quotes.c */
char			*extract_double_quoted(char *str,
					int *i, t_env *env, int *exit_status);

/* lexer_redirect.c */
char			*extract_redirect_filename(char *str, int *i);
char			*extract_word(char *str,
					int *i, t_env *env, int *exit_status);
t_token			*extract_operator(char *str, int *i);

/* lexer.c */
t_token			*lexer(char *line, t_env *env, int *exit_status);

// parser.c parser_create.c parser_create2.c 
t_cmd			*create_cmd(void);
void			free_cmd(t_cmd *cmd);
t_cmd			*parse_tokens(t_token *tokens);
int				finalize_command(t_cmd *cmd, char **args,
					int arg_index, int *exit_status);
t_redirect		*create_redirect(char *filename, int append);
t_heredoc		*create_heredoc(char *delim);
void			cleanup_parse_error(char **args, t_cmd *head, int *exit_status);
void			free_cmd_args(char **args);
void			free_cmd_redirects(t_cmd *cmd);
void			free_cmd_heredocs(t_cmd *cmd);
void			free_cmd_single(t_cmd *cmd);
/* parser_context.c */
t_parse_context	init_parse_context(char **args);
int				finalize_parsing(t_parse_context *ctx, char **args);

// Parser handlers
t_cmd			*init_cmd_if_needed(t_cmd **head, t_cmd **current_cmd);
int				handle_pipe_token(t_parse_context *ctx);
int				handle_word_token(t_token *current, t_parse_context *ctx);
int				handle_heredoc_token(t_token **current, t_parse_context *ctx);
int				handle_redirect_in_token(t_token **current,
					t_parse_context *ctx);
int				handle_redirect_out_token(t_token **current,
					t_parse_context *ctx, int append);

/* Structure pour les données de pipeline */
typedef struct s_pipeline_data
{
	int		stdin_copy;
	int		stdout_copy;
	t_cmd	*current;
	int		prev_fd;
	int		pipe_fd[2];
	int		i;
	t_env	*env;
	pid_t	*pids;
	int		*exit_status;
}	t_pipeline_data;

/* Prototypes pour execute.c */
int				is_builtin(char *cmd_name);
void			execute_builtin(t_cmd *cmd, t_env **env, int *exit_status);
void			execute_cmd(t_cmd *cmd, t_env *env,
					int *exit_status, int is_child);
void			execute_pipeline(t_cmd *pipeline, t_env *env, int *exit_status);

/* Prototypes pour execute_redirects.c */
int				handle_input_redirect(t_cmd *cmd, int *exit_status);
int				handle_output_redirects(t_cmd *cmd, int *exit_status);
int				finalize_output_redirect(t_cmd *cmd, int *exit_status);
int				handle_redirects_wrapper(t_cmd *cmd, int *exit_status);

/* Prototypes pour execute_command.c */
void			execute_command(char **args, t_env *env, int *exit_status);

/* Prototypes pour execute_utils.c */
void			wait_for_child(pid_t pid, int *exit_status);
void			cleanup_and_exit(t_cleanup_data *data);
int				count_pipeline_commands(t_cmd *pipeline);
int				handle_single_builtin(t_cmd *pipeline,
					t_env *env, int *exit_status);
char			*get_path_from_env(char *cmd, t_env *env, int *exit_status);

/* Prototypes pour execute_pipeline.c */
int				setup_and_run_pipeline(t_pipeline_init_context *ctx);

/* Prototypes pour execute_pipeline_utils.c */
void			init_pipeline_data(t_pipeline_data *data,
					t_pipeline_init_context *ctx);
void			update_pipeline_state(t_pipeline_data *data);
void			close_extra_fds(void);

/* builtins_utils.c */
int				is_valid_identifier(const char *str);
int				ft_isdigit_str(char *str);
int				check_echo_option(char *arg);
void			free_env_node(t_env *node);
char			*extract_key(char *arg, char *eq);

/* builtin_echo_env.c */
void			builtin_echo(t_cmd *cmd, t_env **env, int *exit_status);
void			builtin_env(t_cmd *cmd, t_env **env, int *exit_status);
void			builtin_pwd(t_cmd *cmd, t_env **env, int *exit_status);

/* builtin_cd.c */
void			builtin_cd(t_cmd *cmd, t_env **env, int *exit_status);

/* builtin_export.c */
void			export_no_args(t_cmd *cmd, t_env **env, int *exit_status);
void			handle_invalid_key(char *key, int *error_occurred);
t_env			*create_new_env_node(t_env_creation_context *ctx);
void			update_existing_env_var(t_env *current, char *key, char *value);
void			add_new_env_var(t_env **env,
					t_env *prev, t_env_creation_context *ctx);

/* builtin_export2.c */
void			process_export_arg(t_cmd *cmd, t_export_context *ctx);
int				handle_export_without_equals(char *key, int *arg_index);
void			process_variable(char *str, int *i,
					t_env *env, char **result_info);

/* builtin_export3.c */
void			builtin_export(t_cmd *cmd, t_env **env, int *exit_status);
int				handle_export_with_equals(char *key,
					char *eq, t_export_context *ctx);
void			update_env(t_env **env, char *key,
					char *value, int *exit_status);

/* builtin_unset_exit.c */
void			builtin_unset(t_cmd *cmd, t_env **env, int *exit_status);
void			builtin_exit(t_cmd *cmd, t_env **env, int *exit_status);

// env.c
t_env			*create_env_node(char *envp_line);
t_env			*init_env(char **envp);
void			free_env(t_env *env);
char			*get_env_value(t_env *env, char *key);
t_env			*find_path_node(t_env *env);

// env_utils.c
char			*test_path_dir(char *dir, char *cmd);
char			*get_path(char *cmd, t_env *env);
int				count_env_nodes(t_env *env);
void			free_array_partial(char **array, int index);
char			**env_to_array(t_env *env);

// errors.c
void			display_error(const char *cmd, const char *arg,
					const char *message, int *exit_code);
void			display_system_error(const char *cmd,
					const char *arg, int *exit_code);
void			error_command_not_found(const char *cmd, int *exit_code);
void			error_no_such_file(const char *cmd,
					const char *file, int *exit_code);
void			error_permission_denied(const char *cmd,
					const char *file, int *exit_code);
void			error_too_many_args(const char *cmd, int *exit_code);
void			error_numeric_required(const char *cmd,
					const char *arg, int *exit_code);
void			error_home_not_set(int *exit_code);

// heredoc.c
char			*read_heredoc(char *delim, int *exit_status);
int				prepare_heredocs(t_cmd *cmd, int *exit_status);
int				setup_heredoc_pipe(t_cmd *cmd, int *exit_status);

/* heredoc_utils.c */
void			heredoc_sigint_handler(int sig);
void			*setup_heredoc_signals(void (*handler)(int));
char			*append_heredoc_line(char *content, char *line,
					int *exit_status);
char			*handle_heredoc_end(char *content, char *line,
					void (*old_handler)(int), int *exit_status);
int				process_single_heredoc(t_heredoc *heredoc, int *exit_status);

void			cleanup_shell(t_env *env, int exit_status);

#endif