/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:46:33 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 18:19:23 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_syntax_error = false;

static void	perror_prefix(void)
{
	dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
}

void	fatal_error(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	assert_error(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	err_exit(const char *location, const char *msg, int status)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "%s: %s\n", location, msg);
	exit(status);
}

void	todo(const char *msg)
{
	perror_prefix();
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
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
	while (tok && !at_eof(tok))
		tok = tok->next;
	*rest = tok;
}

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}
