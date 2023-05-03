/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step3.exec_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:01:19 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/03 14:33:22 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		interpret(char *const line)
// {
// 	extern char **environ;
// 	char		*argv[] = {line, NULL};
// 	pid_t		pid;
// 	int			wstatus;

// 	pid = fork();
// 	if (pid < 0)
// 		fatal_error("fork");
// 	else if (pid == 0)
// 	{
// 		execve(line, argv, environ);
// 		fatal_error("execve");
// 	}
// 	else
// 	{
// 		wait(&wstatus);
// 		return (WEXITSTATUS(wstatus));
// 	}
// }

static void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

static int	exec(char **argv)
{
	extern char		**environ;
	const	char	*path = argv[0];
	pid_t			pid;
	int				wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
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

void	interpret(char *line, int *stat_loc)
{
	t_token	*tok;
	char 	**argv;

	tok = tokenize(line);
	if (tok->kind == TK_EOF)
		;
	else
	{
		argv = token_list_to_argv(tok);
		*stat_loc = exec(argv);
		free_argv(argv);
	}
	free_tok(tok);
}
