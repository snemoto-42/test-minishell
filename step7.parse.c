/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step7.parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:30:43 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/03 20:26:24 by snemoto          ###   ########.fr       */
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

static void	append_tok(t_token **tokens, t_token *tok)
{
	if (*tokens == NULL)
	{
		*tokens = tok;
		return ;
	}
	append_tok(&(*tokens)->next, tok);
}

t_node	*parse(t_token *tok)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_CMD);
	while (tok && !at_eof(tok))
	{
		if (tok->kind == TK_WORD)
		{
			append_tok(&node->args, tokdup(tok));
			tok = tok->next;
		}
		else
			parse_error("Unexpected Token", &tok, tok);
	}
	return (node);
}
