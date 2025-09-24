/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*process_operator(char *line, int *i, t_lexer_context *ctx)
{
	t_token	*token;

	token = extract_operator(line, i);
	*ctx->after_redirect = is_redirect_token(token);
	return (token);
}

static t_token	*process_word(char *line, int *i, t_lexer_context *ctx)
{
	t_token	*token;
	char	*word;

	if (*ctx->after_redirect)
		word = extract_redirect_filename(line, i);
	else
		word = extract_word(line, i, ctx->env, ctx->exit_status);
	if (!word)
		return (NULL);
	token = create_token(TOKEN_WORD, word);
	free(word);
	return (token);
}

static t_token	*get_next_token(char *line, int *i, t_lexer_context *ctx)
{
	t_token	*token;
	int		op_len;

	op_len = is_operator(line, *i);
	if (op_len > 0)
		token = process_operator(line, i, ctx);
	else
	{
		token = process_word(line, i, ctx);
		*ctx->after_redirect = 0;
	}
	return (token);
}

static int	process_token(char *line, int *i, t_lexer_context *ctx,
	t_token_list *list)
{
	t_token	*token;

	token = get_next_token(line, i, ctx);
	if (!token)
	{
		return (0);
	}
	add_token(&list->tokens, &list->last, token);
	return (1);
}

t_token	*lexer(char *line, t_env *env, int *exit_status)
{
	t_token_list	list;
	t_lexer_context	ctx;
	int				i;
	int				after_redirect;

	i = 0;
	after_redirect = 0;
	list.tokens = NULL;
	list.last = NULL;
	ctx = (t_lexer_context){env, exit_status, &after_redirect};
	while (line[i])
	{
		skip_whitespace(line, &i);
		if (!line[i])
			break ;
		if (!process_token(line, &i, &ctx, &list))
			return (NULL);
	}
	return (list.tokens);
}
