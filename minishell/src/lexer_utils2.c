/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:24:30 by jeetienn          #+#    #+#             */
/*   Updated: 2024/11/06 01:06:29 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TOKEN_REDIRECT_OUT)
		return (1);
	if (token->type == TOKEN_REDIRECT_APPEND)
		return (1);
	if (token->type == TOKEN_REDIRECT_IN)
		return (1);
	if (token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

void	skip_whitespace(char *line, int *i)
{
	while (line[*i] && is_whitespace(line[*i]))
		(*i)++;
}
