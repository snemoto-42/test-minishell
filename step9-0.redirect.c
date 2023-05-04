/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step9-0.redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:30:43 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 16:46:58 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
}

t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->filename = tokdup(tok->next);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_in(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_IN);
	node->filename = tokdup(tok->next);
	node->targetfd = STDIN_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_append(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_APPEND);
	node->filename = tokdup(tok->next);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

t_node	*redirect_heredoc(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_HEREDOC);
	node->delimiter = tokdup(tok->next);
	if (strchr(node->delimiter->word, SINGLE_QUOTE_CHAR) == NULL
		&& strchr(node->delimiter->word, DOUBLE_QUOTE_CHAR) == NULL)
		node->is_delim_unquoted = true;
	node->targetfd = STDIN_FILENO;
	*rest = tok->next->next;
	return (node);
}
