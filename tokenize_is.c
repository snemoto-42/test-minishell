/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:59 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/05 11:46:55 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_metacharacter(char c)
{
	if (is_blank(c))
		return (true);
	return (c && strchr("|&;()<>\n", c));
}

bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

bool	is_control_operator(t_token *tok)
{
	static char *const	operators[] = {"||", "&", "&&",
		";", ";;", "(", ")", "|", "\n"};
	size_t				i;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(tok->word, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	startswith(const char *s, const char *keyword)
{
	return (memcmp(s, keyword, strlen(keyword)) == 0);
}
