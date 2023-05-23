/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:28:17 by hikaru            #+#    #+#             */
/*   Updated: 2023/05/23 20:35:13 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **cmd, t_list *env_head)
{
	int		i;
	t_list	*tmp;

	i = 1;
	tmp = env_head->next;
	while (cmd[i])
	{
		tmp = env_head->next;
		while (tmp != env_head)
		{
			if (ft_strcmp(cmd[i], tmp->key) == 0)
				delete(env_head, tmp);
			tmp = tmp->next;
		}
		i++;
	}
	return (TRUE);
}
