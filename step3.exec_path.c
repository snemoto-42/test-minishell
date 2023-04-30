/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step3.exec_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:01:19 by snemoto           #+#    #+#             */
/*   Updated: 2023/04/30 13:44:37 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(const char *msg) __attribute__((noreturn));

void	fatal_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

int		interpret(char *line)
{
	extern char **environ;
	char		*argv[] = {line, NULL};
	pid_t		pid;
	int			wstatus;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		execve(line, argv, environ);
		fatal_error("execve");
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}
