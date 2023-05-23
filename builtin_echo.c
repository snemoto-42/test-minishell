/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:24:57 by hikaru            #+#    #+#             */
/*   Updated: 2023/05/23 19:59:09 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[i])
	{
		dprintf(STDOUT_FILENO, "\n");
		return (TRUE);
	}
	if (ft_strcmp(cmd[i], "-n") == 0)
		i = 2;
	while (cmd[i])
	{
		dprintf(STDOUT_FILENO, "%s", cmd[i]);
		if (cmd[++i])
			dprintf(STDOUT_FILENO, " ");
	}
	if (ft_strcmp(cmd[1], "-n") != 0)
		dprintf(STDOUT_FILENO, "\n");
	return (TRUE);
}
