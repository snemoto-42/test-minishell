/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:52 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/23 20:43:25 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_var;

static void	init_g_var(t_global g_var)
{
	g_var.g_sig = 0;
	g_var.g_syntax_error = false;
	g_var.g_rl_interrupted = false;
	g_var.g_last_status = 0;
}

static void	handle_line(char *line, int *stat_loc, t_list *head)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	if (is_eof(tok))
		;
	else if (g_var.g_syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(&tok, tok);
		if (g_var.g_syntax_error)
			*stat_loc = ERROR_PARSE;
		else
		{
			*stat_loc = expand_and_exec(node, head);
		}
		free_node(node);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;
	t_list	*head;

	rl_outstream = stderr;
	setup_signal();
	init_g_var(g_var);
	head = env_to_list(environ);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		handle_line(line, &g_var.g_last_status, head);
		free(line);
	}
	exit(g_var.g_last_status);
}
