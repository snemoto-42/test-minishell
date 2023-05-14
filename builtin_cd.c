/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:26:04 by hikaru            #+#    #+#             */
/*   Updated: 2023/05/08 15:38:44 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chdir(char **cmd, DIR *dir)
{
	struct dirent	*dp;

	dp = readdir(dir);
	while (dp != NULL)
	{
		if (ft_strcmp(cmd[1], dp->d_name) == 0)
		{
			dprintf(2, "bash: cd: %s: Not a directory\n", cmd[1]);
			break ;
		}
		dp = readdir(dir);
	}
	if (!dp)
		dprintf(2, "bash: cd: %s: No such file or directory\n", cmd[1]);
}

int	ft_cd(char **cmd, char *cwd)
{
	DIR				*dir;

	if (!cmd[1])
		chdir(ft_strjoin("/Users/", getlogin()));
	else if (chdir(cmd[1]) == -1)
	{
		dir = opendir(getcwd(cwd, 512));
		if (dir == NULL)
			dprintf(2, "bash: cd: %s: No such file or directory\n", cmd[1]);
		else
			ft_chdir(cmd, dir);
		exit(1);
	}
	return (TRUE);
}
