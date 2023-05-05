# minishell
The following is the file structure and function descriptions for minishell.
UPDATED 2023/05/05

## 	destructor.c
	void	free_node(t_node *node);
TEXTTEXT
	void	free_tok(t_token *tok);
TEXTTEXT
	void	free_argv(char **argv);
TEXTTEXT

## error_location.c
	void	xperror(const char *location);
TEXTTEXT
	void	tokenize_error(const char *location, char **rest, char *line);
TEXTTEXT
	void	parse_error(const char *location, t_token **rest, t_token *tok);
TEXTTEXT

## error_msg.c
	void	perror_prefix(void);
TEXTTEXT
	void	fatal_error(const char *msg) __attribute__((noreturn));
TEXTTEXT
	void	assert_error(const char *msg) __attribute__((noreturn));
TEXTTEXT
	void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
TEXTTEXT

## exec.c

## expand_append.c

## expand_is.c

## expand_remove.c

## expand_var.c

## main.c

## parse_append.c

## parse.c

## pipe.c

## redirect_op.c

## redirect_util.c

## redirect.c

## signal_util.c

## signal.c

## tokenize_is.c

## tokenize_to_argv.c

## tokenize_word.c

## tokenize.c
