/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:27:32 by hikaru            #+#    #+#             */
/*   Updated: 2023/05/23 19:58:58 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd)
{
	if (cmd[1] && cmd[2])
	{
		dprintf(STDERR_FILENO, "bash: exit: too many arguments\n");
		exit(255);
	}
	else if (cmd[1])
	{
		if (atoi_check(cmd[1]) == TRUE)
			exit(ft_atoi(cmd[1]));
		dprintf(2, "bash: exit: %s: numeric argument required\n", cmd[1]);
		exit(255);
	}
	exit(0);
}
