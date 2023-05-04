/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step7.parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:30:43 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 13:12:08 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

static t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
	return (node);
}

static t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}

static void	append_tok(t_token **tok, t_token *elm)
{
	if (*tok == NULL)
	{
		*tok = elm;
		return ;
	}
	append_tok(&(*tok)->next, elm);
}

static void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}

static bool	equal_op(t_token *tok, char *op)
{
	if (tok->kind != TK_OP)
		return (false);
	return (strcmp(tok->word, op) == 0);
}

static t_node	*redirect_out(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_REDIR_OUT);
	node->filename = tokdup(tok->next);
	node->targetfd = STDOUT_FILENO;
	*rest = tok->next->next;
	return (node);
}

static void	append_command_element(t_node *command, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&command->args, tokdup(tok));
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_out(&tok, tok));
	else
		todo("append_command_element");
	*rest = tok;
}

t_node	*parse(t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &tok, tok);
	while (tok && !at_eof(tok))
		append_command_element(node, &tok, tok);
	return (node);
}
