/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_location.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:46:33 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/05 11:21:52 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_syntax_error = false;

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	g_syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax error near unexpected character '%c' in %s\n", *line, location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *tok)
{
	g_syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax error near unexpected token '%s' in %s\n", tok->word, location);
	while (tok && !is_eof(tok))
		tok = tok->next;
	*rest = tok;
}
