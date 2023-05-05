/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_location.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:46:33 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/05 13:59:48 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	xperror(const char *location)
{
	perror_prefix();
	perror(location);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	g_var.g_syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax err near '%c' in %s\n", *line, location);
	while (*line)
		line++;
	*rest = line;
}

void	parse_error(const char *location, t_token **rest, t_token *tok)
{
	g_var.g_syntax_error = true;
	perror_prefix();
	dprintf(STDERR_FILENO, "syntax err near '%s' in %s\n", tok->word, location);
	while (tok && !is_eof(tok))
		tok = tok->next;
	*rest = tok;
}
