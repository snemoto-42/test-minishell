/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:47 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/03 15:59:39 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'
# define ERROR_TOKENIZE 258

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>

// global var
extern bool	syntax_error;

// step3
void	interpret(char *line, int *stat_loc);

// step4
char	*search_path(const char *filename);

// step5-1
typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
}	t_token_kind;

typedef struct s_token t_token;

struct s_token
{
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

bool	consume_blank(char **rest, char *line);
bool	startswith(const char *s, const char *keyword);
bool	is_metacharacter(char c);
bool	is_operator(const char *s);
bool 	is_word(const char *s);

t_token	*tokenize(char *line);

char	**token_list_to_argv(t_token *tok);

// step5-2
void	expand(t_token *tok);

// others
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	todo(const char *msg) __attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);

void	free_tok(t_token *tok);
void	free_argv(char **argv);

#endif
