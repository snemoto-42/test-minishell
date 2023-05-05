/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:52 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/05 11:36:58 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_status = 0;

static void	expand(t_node *node)
{
	expand_variable(node);
	expand_quote_removal(node);
}

static int	exec(t_node *node)
{
	pid_t	last_pid;
	int		status;

	if (open_redir_file(node) < 0)
		return (ERRPR_OPEN_REDIR);
	last_pid = exec_pipeline(node);
	status = wait_pipeline(last_pid);
	return (status);
}

static void	interpret(char *line, int *stat_loc)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	if (is_eof(tok))
		;
	else if (g_syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(tok);
		if (g_syntax_error)
			*stat_loc = ERROR_PARSE;
		else
		{
			expand(node);
			*stat_loc = exec(node);
		}
		free_node(node);
	}
	free_tok(tok);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	setup_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &g_last_status);
		free(line);
	}
	exit(g_last_status);
}

// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
// system("leaks -q minishell");
// }
