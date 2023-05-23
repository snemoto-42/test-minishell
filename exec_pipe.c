/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:01:19 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/23 20:18:23 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				status = 128 + WTERMSIG(wstatus);
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}

static void	validate_access(const char *path, const char *filename)
{
	if (path == NULL)
		err_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		err_exit(filename, "command not found", 127);
}

static void	exec_child(t_list *head, char **argv)
{
	char	*path;
	char	**array;

	path = argv[0];
	if (strchr(path, '/') == NULL)
		path = search_path(path);
	validate_access(path, argv[0]);
	array = list_to_array(head);
	execve(path, argv, array);
	fatal_error("execve");
}

static pid_t	exec_pipeline(t_node *node, t_list *head, char **argv)
{
	pid_t	pid;

	if (node == NULL)
		return (-1);
	prepare_pipe(node);
	argv = token_list_to_argv(node->command->args);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		reset_signal();
		prepare_pipe_child(node);
		do_redirect(node->command->redirects);
		if (is_builtin(argv) == FALSE)
			exec_child(head, argv);
		else
			built_in_cmd(argv, head);
		reset_redirect(node->command->redirects);
	}
	close_pipe(node);
	if (node->next)
		return (exec_pipeline(node->next, head, argv));
	return (pid);
}

int	expand_and_exec(t_node *node)
{
	pid_t	last_pid;
	int		status;
	t_list	*head;
	char	**argv;

	expand_variable(node);
	expand_quote_removal(node);
	if (open_redir_file(node) < 0)
		return (ERRPR_OPEN_REDIR);
	head = env_to_list(environ);
	argv = token_list_to_argv(node->command->args);
	if (is_builtin(argv) != FALSE)
	{
		do_redirect(node->command->redirects);
		built_in_cmd(argv, head);
		status = 0;
	}
	else
	{
		last_pid = exec_pipeline(node, head, argv);
		status = wait_pipeline(last_pid);
	}
	return (status);
}
