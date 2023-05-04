/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:47 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 16:32:07 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR_TOKENIZE 258
# define ERROR_PARSE 258
# define ERRPR_OPEN_REDIR 1
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'
# define ERROR_PREFIX "minishell: "

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <ctype.h>

extern int	last_status;
extern bool	syntax_error;

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

typedef enum e_node_kind
{
	ND_PIPELINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
}	t_node_kind;

typedef struct	s_node t_node;

struct s_node
{
	t_node_kind	kind;
	t_node		*next;
	t_token		*args;
	t_node		*redirects;
	int			targetfd;
	t_token		*filename;
	t_token		*delimiter;
	int			filefd;
	int			stashed_targetfd;
	int			inpipe[2];
	int			outpipe[2];
	t_node		*command;
};

void	fatal_error(const char *msg) __attribute__((noreturn));
void	assert_error(const char *msg) __attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
void	todo(const char *msg) __attribute__((noreturn));
void	tokenize_error(const char *location, char **rest, char *line);
void	parse_error(const char *location, t_token **rest, t_token *tok);
void	xperror(const char *location);

void	free_node(t_node *node);
void	free_tok(t_token *tok);
void	free_argv(char **argv);

void	interpret(char *line, int *stat_loc);

char	*search_path(const char *filename);

bool	consume_blank(char **rest, char *line);
bool	startswith(const char *s, const char *keyword);
bool	is_metacharacter(char c);
bool	is_control_operator(t_token *tok);
bool 	is_word(const char *s);
bool	is_redirection_operator(const char *s);

t_token	*new_token(char *word, t_token_kind kind);
t_token	*tokdup(t_token *tok);
t_token	*tokenize(char *line);

char	**token_list_to_argv(t_token *tok);

t_node	*parse(t_token *tok);
bool	at_eof(t_token *tok);

void	append_char(char **s, char c);
void	expand(t_node *node);

void	expand_variable(t_node *node);

int		open_redir_file(t_node *redir);
void	do_redirect(t_node *redir);
void	reset_redirect(t_node *redir);

bool	equal_op(t_token *tok, char *op);
t_node	*redirect_out(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node	*redirect_append(t_token **rest, t_token *tok);
t_node	*redirect_heredoc(t_token **rest, t_token *tok);

t_node	*new_node(t_node_kind kind);

void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

#endif
