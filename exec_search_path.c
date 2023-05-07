/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_search_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:01:19 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/07 11:06:22 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_path(const char *path)
{
	char	*dup;

	if (access(path, X_OK) == 0)
	{	
		dup = strdup(path);
		if (dup == NULL)
			fatal_error("strdup");
		return (dup);
	}
	return (NULL);
}

char	*search_path(const char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = getenv("PATH");
	while (*value)
	{
		bzero(path, PATH_MAX);
		end = strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			strlcpy(path, value, PATH_MAX);
		strlcat(path, "/", PATH_MAX);
		strlcat(path, filename, PATH_MAX);
		dup = check_path(path);
		if (dup != NULL)
			return (dup);
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}
