/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:57:28 by hmorisak          #+#    #+#             */
/*   Updated: 2023/05/23 20:04:21 by snemoto          ###   ########.fr       */
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

int	is_builtin(char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") != 0 && ft_strcmp(cmd[0], "cd") != 0
		&& ft_strcmp(cmd[0], "pwd") != 0 && ft_strcmp(cmd[0], "export") != 0
		&& ft_strcmp(cmd[0], "unset") != 0 && ft_strcmp(cmd[0], "env") != 0
		&& ft_strcmp(cmd[0], "exit") != 0)
		return (FALSE);
	return (TRUE);
}

int	built_in_cmd(char **cmd, t_list *env_head)
{
	char	cwd[512];

	ft_memset(cwd, '\0', 512);
	if (is_builtin(cmd) == FALSE)
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
	return (TRUE);
}
