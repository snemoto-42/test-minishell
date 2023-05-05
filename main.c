/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:52 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/05 17:41:15 by snemoto          ###   ########.fr       */
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

static void	interpret(char *line, int *stat_loc)
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
		node = parse(tok);
		if (g_var.g_syntax_error)
			*stat_loc = ERROR_PARSE;
		else
			*stat_loc = expand_and_exec(node);
		free_node(node);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	setup_signal();
	init_g_var(g_var);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &g_var.g_last_status);
		free(line);
	}
	exit(g_var.g_last_status);
}
