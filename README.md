# minishell
The following is the file structure and function descriptions for minishell.

UPDATED 2023/05/05

## destructor.c
```
void	free_tok(t_token *tok);
```
・再帰的にnode->wordとnodeをfreeしていく

```
void	free_node(t_node *node);
```
・再帰的にtokとnodeをfreeしていく

## error.c
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

```
void	xperror(const char *location);
```
・perrorの呼び出し、redirect.cでのみ使用

```
void	tokenize_error(const char *location, char **rest, char *line);
```
・tokenize系で使用

## exec_pipe_prepare.c
```
static void	cpy_pipe(int dst[2], int src[2]);
```
TEXTTEXT

```
void	prepare_pipe(t_node *node);
```
TEXTTEXT

```
void	prepare_pipe_child(t_node *node);
```
TEXTTEXT

```
void	prepare_pipe_parent(t_node *node);
```
TEXTTEXT

## exec_pipe.c
```
static char	*search_path(const char *filename);
```
TEXTTEXT

```
static void	validate_access(const char *path, const char *filename);
```
TEXTTEXT

```
static pid_t	exec_pipeline(t_node *node);
```
TEXTTEXT

```
static int		wait_pipeline(pid_t last_pid);
```
TEXTTEXT

```
int	expand_and_exec(t_node *node);
```
・変数variable展開->quote削除の順にnodeを変更していく。

・nodeの種類kindに応じたリダイレクト処理、コマンドの実行を行う。

## exec_token_to_argv.c
```
static char	**tail_recursive(t_token *tok, int nargs, char **argv);
```
TEXTTEXT

```
char	**token_list_to_argv(t_token *tok);
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
```
void	expend_special_parameter_str(char **dst, char **rest, char *p);
```
TEXTTEXT

```
void	expand_variable_str(char **dst, char **rest, char *p);
```
TEXTTEXT

```
static void	expand_variable_tok(t_token *tok);
```
TEXTTEXT

```
void	expand_variable(t_node *node);
```
TEXTTEXT

```
char	*expand_heredoc_line(char *line);
```
TEXTTEXT

## main.c
```
static void	init_g_var(t_global g_var);
```
TEXTTEXT

```
static void	interpret(char *line, int *stat_loc);
```
・tokenize->parse->expand->execの順にプロンプトに入力されたlineを実行していく。

```
int	main(void);
```
・テストでdiffをとるため、readlineの出力先をstderrに変更。

## parse_append.c
```
static void	append_tok(t_token **tok, t_token *elm);
```
TEXTTEXT

```
static void	append_node(t_node **node, t_node *elm);
```
TEXTTEXT

```
t_token	*tokdup(t_token *tok);
```
TEXTTEXT

```
void	append_command_element(t_node *command, t_token **rest, t_token *tok);
```
TEXTTEXT

## parse.c
```
bool	is_eof(t_token *tok);
```
TEXTTEXT

```
t_node	*new_node(t_node_kind kind);
```
TEXTTEXT

```
static t_node	*simple_command(t_token **rest, t_token *tok);
```
TEXTTEXT

```
static t_node	*pipeline(t_token **rest, t_token *tok);
```
TEXTTEXT

```
t_node	*parse(t_token *tok);
```
TEXTTEXT

## redirect_op.c
```
t_node	*redirect_out(t_token **rest, t_token *tok);
```
TEXTTEXT

```
t_node	*redirect_in(t_token **rest, t_token *tok);
```
TEXTTEXT

```
t_node	*redirect_append(t_token **rest, t_token *tok);
```
TEXTTEXT

```
t_node	*redirect_heredoc(t_token **rest, t_token *tok);
```
TEXTTEXT

## redirect_util.c
```
bool	equal_op(t_token *tok, char *op);
```
TEXTTEXT

```
bool	is_redirect(t_node *node);
```
TEXTTEXT

```
int		stashfd(int fd);
```
TEXTTEXT

```
int		read_heredoc(const char *delimiter, bool is_delim_unquoted);
```
TEXTTEXT

## redirect.c
```
int		open_redir_file(t_node *redir);
```
TEXTTEXT

```
void	do_redirect(t_node *redir);
```
TEXTTEXT

```
void	reset_redirect(t_node *redir);
```
TEXTTEXT

## signal_util.c
```
static void	handler(int signum)
```
TEXTTEXT

```
void	reset_sig(int signum);
```
TEXTTEXT

```
void	ignore_sig(int signum);
```
TEXTTEXT

```
void	setup_sigint(void);
```
TEXTTEXT

```
int		check_state(void);
```
TEXTTEXT

## signal.c
```
void	setup_signal(void);
```
TEXTTEXT

```
void	reset_signal(void);
```
TEXTTEXT

## tokenize_is.c
```
bool	is_blank(char c);
```
TEXTTEXT

```
bool	is_metacharacter(char c);
```
TEXTTEXT

```
bool	is_word(const char *s);
```
TEXTTEXT

```
bool	is_control_operator(t_token *tok);
```
TEXTTEXT

```
bool	startswith(const char *s, const char *keyword);
```
TEXTTEXT

## tokenize_word.c
```
static bool	word_single_quote(char **rest, char *line);
```
TEXTTEXT

```
static bool	word_double_quote(char **rest, char *line);
```
TEXTTEXT

```
t_token	*word(char **rest, char *line);
```
TEXTTEXT

## tokenize.c
```
static bool	consume_blank(char **rest, char *line);
```
TEXTTEXT

```
t_token	*new_token(char *word, t_token_kind kind);
```
TEXTTEXT

```
static t_token	*operator(char **rest, char *line);
```
TEXTTEXT

```
t_token	*tokenize(char *line);
```
TEXTTEXT
