/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step5-1.tokenize_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:59 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 19:33:38 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	word_single_quote(char **rest, char *line)
{
	line++;
	while (*line != SINGLE_QUOTE_CHAR)
		line++;
	if (*line == '\0')
	{
		tokenize_error("Unclosed single quote", &line, line);
		return (false);
	}
	else
		line++;
	*rest = line;
	return (true);
}

static bool	word_double_quote(char **rest, char *line)
{
	line++;
	while (*line != DOUBLE_QUOTE_CHAR)
		line++;
	if (*line == '\0')
	{
		tokenize_error("Unclosed double quote", &line, line);
		return (false);
	}
	else
		line++;
	*rest = line;
	return (true);
}

t_token	*word(char **rest, char *line)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
		{
			if (word_single_quote(&line, line) == false)
				break ;
		}
		else if (*line == DOUBLE_QUOTE_CHAR)
		{
			if (word_double_quote(&line, line) == false)
				break ;
		}
		else
			line++;
	}
	word = strndup(start, line - start);
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}
