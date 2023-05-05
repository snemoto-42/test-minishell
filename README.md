# minishell
The following is the file structure and function descriptions for minishell.
UPDATED 2023/05/05

## 	destructor.c
```
void	free_node(t_node *node);
```
TEXTTEXT

```
void	free_tok(t_token *tok);
```
TEXTTEXT

```
void	free_argv(char **argv);
```
TEXTTEXT

## error_location.c
```
void	xperror(const char *location);
```
TEXTTEXT

```
void	tokenize_error(const char *location, char **rest, char *line);
```
TEXTTEXT

```
void	parse_error(const char *location, t_token **rest, t_token *tok);
```
TEXTTEXT

## error_msg.c
```
void	perror_prefix(void);
```
TEXTTEXT

```
void	fatal_error(const char *msg) __attribute__((noreturn));
```
TEXTTEXT

```
void	assert_error(const char *msg) __attribute__((noreturn));
```
TEXTTEXT

```
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
```
TEXTTEXT

## expand_append.c
```
void	append_char(char **s, char c);
```
TEXTTEXT

```
void	append_num(char **dst, unsigned int num);
```
TEXTTEXT

```
void	append_single_quote(char **dst, char **rest, char *p);
```
TEXTTEXT

```
void	append_double_quote(char **dst, char **rest, char *p);
```
TEXTTEXT

## expand_is.c
```
bool	is_alpha_under(char c);
```
TEXTTEXT

```
bool	is_alpha_num_under(char c);
```
TEXTTEXT

```
bool	is_variable(char *s);
```
TEXTTEXT

```
bool	is_special_parameter(char *s);
```
TEXTTEXT

## expand_remove.c
```
static void	remove_single_quote(char **dst, char **rest, char *p);
```
TEXTTEXT

```
static void	remove_double_quote(char **dst, char **rest, char *p);
```
TEXTTEXT

```
static void	remove_quote(t_token *tok);
```
TEXTTEXT

```
void	expand_quote_removal(t_node *node);
```
TEXTTEXT

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
