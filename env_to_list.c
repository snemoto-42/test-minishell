/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:03:24 by hikaru            #+#    #+#             */
/*   Updated: 2023/05/14 14:05:12 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert(t_list *head, t_list *list)
{
	head->prev->next = list;
	list->prev = head->prev;
	head->prev = list;
	list->next = head;
	head->count++;
}

void	delete(t_list *head, t_list *list)
{
	list->prev->next = list->next;
	list->next->prev = list->prev;
	free(list->key);
	free(list->value);
	free(list);
	head->count--;
}

t_list	*free_list(t_list *head)
{
	t_list	*list;
	t_list	*tmp;

	list = head->next;
	tmp = list;
	while (list != head)
	{
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = tmp;
	}
	return (NULL);
}

static t_list	*make_list(t_list *head, int i)
{
	size_t			pos;
	t_list			*list;

	pos = 0;
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	while (environ[i][pos] != '=')
		pos++;
	list->key = ft_substr(environ[i], 0, pos);
	if (!list->key)
		return (free_list(head));
	list->value = ft_substr(environ[i], pos + 1, ft_strlen(environ[i]));
	if (!list->value)
		return (free_list(head));
	list->sort_flag = 0;
	if (ft_strcmp(list->key, "_") == 0)
		list->sort_flag = 1;
	insert(head, list);
	return (head);
}

t_list	*env_to_list(char **environ)
{
	t_list	*head;
	int		i;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->count = 0;
	head->next = head;
	head->prev = head;
	i = 0;
	while (environ[i])
	{
		if (make_list(head, i) == NULL)
			return (NULL);
		i++;
	}
	return (head);
}
