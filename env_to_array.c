/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:26:58 by hmorisak          #+#    #+#             */
/*   Updated: 2023/05/14 14:00:41 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**list_to_array(t_list *env_head)
{
	int		i;
	t_list	*tmp;
	char	**array;

	i = 0;
	tmp = env_head->next;
	array = (char **)malloc(sizeof(char *) * (env_head->count + 1));
	if (!array)
		return (NULL);
	while (i < env_head->count && tmp != env_head)
	{
		array[i] = ft_strdup(tmp->value);
		if (!array[i])
			return (free_array(array));
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
