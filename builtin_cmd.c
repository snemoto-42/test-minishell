/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:57:28 by hmorisak          #+#    #+#             */
/*   Updated: 2023/05/08 15:14:43 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (TRUE);
}

int	built_in_cmd(char **cmd, t_list *env_head, t_node *node)
{
	char	cwd[512];

	ft_memset(cwd, '\0', 512);
	if (ft_strcmp(cmd[0], "echo") != 0 && ft_strcmp(cmd[0], "cd") != 0
		&& ft_strcmp(cmd[0], "pwd") != 0 && ft_strcmp(cmd[0], "export") != 0
		&& ft_strcmp(cmd[0], "unset") != 0 && ft_strcmp(cmd[0], "env") != 0
		&& ft_strcmp(cmd[0], "exit") != 0)
		return (FALSE);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd, cwd));
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(cwd));
	if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, env_head));
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(cmd, env_head));
	if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(env_head));
	if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd);
	free_cmd(cmd);
	reset_redirect(node->command->redirects);
	return (TRUE);
}
