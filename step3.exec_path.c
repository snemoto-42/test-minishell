/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step3.exec_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:01:19 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 13:11:44 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

static int	exec_cmd(t_node *node)
{
	extern char		**environ;
	char			*path;
	pid_t			pid;
	int				wstatus;
	char			**argv;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		argv = token_list_to_argv(node->args);
		path = argv[0];
		if (strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		execve(path, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}

static int	exec(t_node *node)
{
	int	status;

	open_redir_file(node->redirects);
	do_redirect(node->redirects);
	status = exec_cmd(node);
	reset_redirect(node->redirects);
	return (status);
}

void	interpret(char *line, int *stat_loc)
{
	t_token	*tok;
	t_node	*node;

	tok = tokenize(line);
	if (at_eof(tok))
		;
	else if (syntax_error)
		*stat_loc = ERROR_TOKENIZE;
	else
	{
		node = parse(tok);
		if (syntax_error)
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
