/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:47 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/05 15:59:17 by snemoto          ###   ########.fr       */
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

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_OP,
	TK_EOF,
}	t_token_kind;

typedef enum e_node_kind
{
	ND_PIPELINE,
	ND_SIMPLE_CMD,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
}	t_node_kind;

typedef struct s_global
{
	volatile sig_atomic_t	g_sig;
	bool					g_syntax_error;
	bool					g_readline_interrupted;
	int						g_last_status;
}	t_global;

extern t_global				g_var;

typedef struct s_token		t_token;
typedef struct s_node		t_node;

struct s_token
{
	char					*word;
	t_token_kind			kind;
	t_token					*next;
};

struct s_node
{
	t_node_kind				kind;
	t_node					*next;
	t_node					*redirects;
	t_node					*command;
	t_token					*args;
	t_token					*filename;
	t_token					*delim;
	bool					is_delim_unquote;
	int						targetfd;
	int						filefd;
	int						stashed_targetfd;
	int						inpipe[2];
	int						outpipe[2];
};

// destructor
void	free_tok(t_token *tok);
void	free_node(t_node *node);

// error
void	fatal_error(const char *msg)
		__attribute__((noreturn));
void	assert_error(const char *msg)
		__attribute__((noreturn));
void	err_exit(const char *location, const char *msg, int status)
		__attribute__((noreturn));
void	xperror(const char *location);
void	tokenize_error(const char *location, char **rest, char *line);

// exec
int		expand_and_exec(t_node *node);

void	prepare_pipe(t_node *node);
void	prepare_pipe_child(t_node *node);
void	prepare_pipe_parent(t_node *node);

char	**token_list_to_argv(t_token *tok);

// expand
void	append_char(char **s, char c);
void	append_num(char **dst, unsigned int num);
void	append_single_quote(char **dst, char **rest, char *p);
void	append_double_quote(char **dst, char **rest, char *p);

bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_variable(char *s);
bool	is_special_parameter(char *s);

void	expand_quote_removal(t_node *node);

void	expend_special_parameter_str(char **dst, char **rest, char *p);
void	expand_variable_str(char **dst, char **rest, char *p);
void	expand_variable(t_node *node);
char	*expand_heredoc_line(char *line);

// parse
t_token	*tokdup(t_token *tok);
void	append_command_element(t_node *command, t_token **rest, t_token *tok);

bool	is_eof(t_token *tok);
t_node	*new_node(t_node_kind kind);
t_node	*parse(t_token *tok);

// redirect
t_node	*redirect_out(t_token **rest, t_token *tok);
t_node	*redirect_in(t_token **rest, t_token *tok);
t_node	*redirect_append(t_token **rest, t_token *tok);
t_node	*redirect_heredoc(t_token **rest, t_token *tok);

bool	equal_op(t_token *tok, char *op);
bool	is_redirect(t_node *node);
int		stashfd(int fd);
int		read_heredoc(const char *delimiter, bool is_delim_unquoted);

int		open_redir_file(t_node *redir);
void	do_redirect(t_node *redir);
void	reset_redirect(t_node *redir);

// signal
void	reset_sig(int signum);
void	ignore_sig(int signum);
void	setup_sigint(void);
int		check_state(void);

void	setup_signal(void);
void	reset_signal(void);

// tokenize
bool	is_blank(char c);
bool	is_metacharacter(char c);
bool	is_word(const char *s);
bool	is_control_operator(t_token *tok);
bool	startswith(const char *s, const char *keyword);

t_token	*word(char **rest, char *line);

t_token	*new_token(char *word, t_token_kind kind);
t_token	*tokenize(char *line);

#endif
