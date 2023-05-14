/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:24:57 by hikaru            #+#    #+#             */
/*   Updated: 2023/05/07 22:25:08 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[i])
		dprintf(1, "\n");
	if (ft_strcmp(cmd[i], "-n") == 0)
		i = 2;
	while (cmd[i])
	{
		dprintf(1, "%s", cmd[i]);
		if (cmd[++i])
			dprintf(1, " ");
	}
	if (ft_strcmp(cmd[1], "-n") != 0)
		dprintf(1, "\n");
	return (TRUE);
}
