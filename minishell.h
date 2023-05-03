/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:47 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/03 20:17:10 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'
# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERROR_PREFIX "minishell: "

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

t_token	*new_token(char *word, t_token_kind kind);
t_token	*tokenize(char *line);

char	**token_list_to_argv(t_token *tok);

// step7
typedef enum e_node_kind
{
	ND_SIMPLE_CMD,
}	t_node_kind;

typedef struct	s_node t_node;

struct s_node
{
	t_token		*args;
	t_node_kind	kind;
	t_node		*next;
};

t_node	*parse(t_token *tok);
bool	at_eof(t_token *tok);

// step5-2
void	expand(t_node *node);

// others
void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	todo(const char *msg) __attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);
void	parse_error(const char *location, t_token **rest, t_token *tok);

void	free_node(t_node *node);
void	free_tok(t_token *tok);
void	free_argv(char **argv);

#endif
