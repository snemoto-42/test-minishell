/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step7.parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:30:43 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 18:35:15 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	at_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
		fatal_error("calloc");
	node->kind = kind;
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
	else if (equal_op(tok, "<") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_in(&tok, tok));
	else if (equal_op(tok, ">>") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_append(&tok, tok));
	else if (equal_op(tok, "<<") && tok->next->kind == TK_WORD)
		append_node(&command->redirects, redirect_heredoc(&tok, tok));
	else
		todo("append_command_element");
	*rest = tok;
}

static t_node	*simple_command(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	append_command_element(node, &tok, tok);
	while (tok && !at_eof(tok) && !is_control_operator(tok))
		append_command_element(node, &tok, tok);
	*rest = tok;
	return (node);
}

static t_node	*pipeline(t_token **rest, t_token *tok)
{
	t_node	*node;

	node = new_node(ND_PIPELINE);
	node->inpipe[0] = STDIN_FILENO;
	node->inpipe[1] = -1;
	node->outpipe[0] = -1;
	node->outpipe[1] = STDOUT_FILENO;
	node->command = simple_command(&tok, tok);
	if (equal_op(tok, "|"))
		node->next = pipeline(&tok, tok->next);
	*rest = tok;
	return (node);
}

t_node	*parse(t_token *tok)
{
	return (pipeline(&tok, tok));
}
