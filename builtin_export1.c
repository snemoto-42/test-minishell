/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:18:27 by hikaru            #+#    #+#             */
/*   Updated: 2023/05/08 15:26:38 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_append(t_list *list, t_list *env_head)
{
	t_list	*tmp;
	char	*value_cpy;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		if (strcmp(tmp->key, list->key) == 0)
		{
			value_cpy = ft_strdup(tmp->value);
			free(tmp->value);
			tmp->value = ft_strjoin(value_cpy, list->value);
			free(value_cpy);
			free(list->key);
			free(list->value);
			free(list);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}

void	export_append(char **cmd, t_list *env_head, int i, int len)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		exit(1);
	list->sort_flag = 0;
	list->key = ft_substr(cmd[i], 0, len);
	if (!list->key)
		exit(1);
	if (cmd[i][len + 2] == '\0')
		list->value = ft_strdup("");
	else
		list->value = ft_substr(cmd[i], len + 2, ft_strlen(cmd[i]));
	if (!list->value)
		exit(1);
	if (is_append(list, env_head) == FALSE)
		insert(env_head, list);
}

int	is_new_key(t_list *env_head, t_list *new_list)
{
	t_list	*list;

	list = env_head->next;
	while (list != env_head)
	{
		if (strcmp(list->key, new_list->key) == 0)
		{
			free(list->value);
			list->value = ft_strdup(new_list->value);
			free(new_list->key);
			free(new_list->value);
			free(new_list);
			return (FALSE);
		}
		list = list->next;
	}
	return (TRUE);
}

void	export_equal(char **cmd, t_list *env_head, int i, int len)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		exit(1);
	list->sort_flag = 0;
	list->key = ft_substr(cmd[i], 0, len);
	if (!list->key)
		exit(1);
	if (cmd[i][len + 1] == '\0')
		list->value = ft_strdup("");
	else
		list->value = ft_substr(cmd[i], len + 1, ft_strlen(cmd[i]));
	if (!list->value)
		exit(1);
	if (is_new_key(env_head, list) == TRUE)
		insert(env_head, list);
}

void	do_export(char **cmd, t_list *env_head, int i)
{
	int		j;

	if (ft_strchr(cmd[i], '=') == NULL)
		non_equal(cmd, env_head, i);
	else
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '+' && cmd[i][j + 1] == '=')
				return (export_append(cmd, env_head, i, j));
			else if (cmd[i][j] == '=')
				return (export_equal(cmd, env_head, i, j));
			else if (('a' <= cmd[i][j] && cmd[i][j] <= 'z')
				|| ('A' <= cmd[i][j] && cmd[i][j] <= 'Z')
				|| cmd[i][j] == '_' || ('0' <= cmd[i][j] && cmd[i][j] <= '9'))
				j++;
			else
			{
				dprintf(1, "%d, %c\n", j, cmd[i][j]);
				dprintf(1, "bash: export: `%s':\
				 not a valid identifier\n", cmd[i]);
				exit(1);
			}
		}
	}
}
