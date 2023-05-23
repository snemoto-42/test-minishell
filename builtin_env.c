/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:28:54 by hikaru            #+#    #+#             */
/*   Updated: 2023/05/23 17:09:49 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env_head)
{
	t_list	*tmp;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		dprintf(STDOUT_FILENO, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (TRUE);
}
