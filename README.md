# minishell
The following is the file structure and function descriptions for minishell.

UPDATED 2023/05/05

## メモリ確保
- static char	*search_path(const char *filename);
- char			**token_list_to_argv(t_token *tok);
- static char	**tail_recursive(t_token *tok, int nargs, char **argv);
- void			append_char(char **s, char c);
- static void	remove_quote(t_token *tok);
- void			expand_variable_str(char **dst, char **rest, char *p);
- static void	expand_variable_tok(t_token *tok);
- char			*expand_heredoc_line(char *line);
- int			main(void);
- t_token		*tokdup(t_token *tok);
- void			append_command_element(t_node *command, t_token **rest, t_token *tok);
- t_node		*new_node(t_node_kind kind);
- static t_node	*simple_command(t_token **rest, t_token *tok);
- static t_node	*pipeline(t_token **rest, t_token *tok);
- t_node		*redirect_out(t_token **rest, t_token *tok);
- t_node		*redirect_in(t_token **rest, t_token *tok);
- t_node		*redirect_append(t_token **rest, t_token *tok);
- t_node		*redirect_heredoc(t_token **rest, t_token *tok);
- int			read_heredoc(const char *delim, bool is_delim_unquoted);
- t_token		*word(char **rest, char *line);
- t_token		*new_token(char *word, t_token_kind kind);

## メモリ解放
- void			free_tok(t_token *tok);
- void			free_node(t_node *node);
- static void	remove_quote(t_token *tok);
- void			expand_variable_str(char **dst, char **rest, char *p);
- static void	expand_variable_tok(t_token *tok);
- char			*expand_heredoc_line(char *line);
- static void	interpret(char *line, int *stat_loc);
- int			main(void);
- int			read_heredoc(const char *delim, bool is_delim_unquoted);

## destructor.c
```
void	free_tok(t_token *tok);
```
- 再帰的にnode->wordとnodeをfreeしていく

```
void	free_node(t_node *node);
```
- 再帰的にtokとnodeをfreeしていく

## error.c
```
void	fatal_error(const char *msg) __attribute__((noreturn));
```
- TEXTTEXT

```
void	assert_error(const char *msg) __attribute__((noreturn));
```
- TEXTTEXT

```
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
```
- TEXTTEXT

```
void	xperror(const char *location);
```
- perrorの呼び出し、redirect.cでのみ使用

```
void	tokenize_error(const char *location, char **rest, char *line);
```
- tokenize系で使用

## exec_heredoc.c
```
static char	*expand_heredoc_line(char *line);
```
- TEXTTEXT

```
int		read_heredoc(const char *delim, bool is_delim_unquoted);
```
- TEXTTEXT

## exec_pipe_prepare.c
```
static void	cpy_pipe(int dst[2], int src[2]);
```
- TEXTTEXT

```
void	prepare_pipe(t_node *node);
```
- TEXTTEXT

```
void	prepare_pipe_child(t_node *node);
```
- TEXTTEXT

```
void	prepare_pipe_parent(t_node *node);
```
- TEXTTEXT

## exec_pipe.c
```
static void	validate_access(const char *path, const char *filename);
```
- TEXTTEXT

```
static void		exec_child(t_node *node);
```
- TEXTTEXT

```
static pid_t	exec_pipeline(t_node *node);
```
- TEXTTEXT

```
static int		wait_pipeline(pid_t last_pid);
```
- TEXTTEXT

```
int	expand_and_exec(t_node *node);
```
- 変数variable展開->quote削除の順にnodeを変更していく。
- nodeの種類kindに応じたリダイレクト処理、コマンドの実行を行う。

## exec_redirect_do_reset.c
```
bool	is_redirect(t_node *node);
```
- TEXTTEXT

```
void	do_redirect(t_node *redir);
```
- TEXTTEXT

```
void	reset_redirect(t_node *redir);
```
- TEXTTEXT

## exec_redirect_open.c
```
int		stashfd(int fd);
```
- TEXTTEXT

```
static int	check_redir_file(t_node *node);
```
- TEXTTEXT

```
int		open_redir_file(t_node *redir);
```
- TEXTTEXT

## exec_search_path.c
```
static char	*check_path(const char *path);
```
- TEXTTEXT

```
char	*search_path(const char *filename);
```
- TEXTTEXT

## exec_token_to_argv.c
```
static char	**next_token(t_token *tok, int nargs, char **argv);
```
- TEXTTEXT

```
char	**token_list_to_argv(t_token *tok);
```
- TEXTTEXT

## expand_append.c
```
void	append_num(char **dst, unsigned int num);
```
- TEXTTEXT

```
void	append_char(char **s, char c);
```
- TEXTTEXT

```
void	append_single_quote(char **dst, char **rest, char *p);
```
- TEXTTEXT

```
void	append_double_quote(char **dst, char **rest, char *p);
```
- TEXTTEXT

## expand_is.c
```
bool	is_alpha_under(char c);
```
- TEXTTEXT

```
bool	is_alpha_num_under(char c);
```
- TEXTTEXT

```
bool	is_variable(char *s);
```
- TEXTTEXT

```
bool	is_special_parameter(char *s);
```
- TEXTTEXT

## expand_remove.c
```
static void	remove_single_quote(char **dst, char **rest, char *p);
```
- TEXTTEXT

```
static void	remove_double_quote(char **dst, char **rest, char *p);
```
- TEXTTEXT

```
static void	remove_quote(t_token *tok);
```
- TEXTTEXT

```
void	expand_quote_removal(t_node *node);
```
- TEXTTEXT

## expand_var.c
```
void	expend_special_parameter_str(char **dst, char **rest, char *p);
```
- TEXTTEXT

```
void	expand_variable_str(char **dst, char **rest, char *p);
```
- TEXTTEXT

```
static void	expand_variable_tok(t_token *tok);
```
- TEXTTEXT

```
void	expand_variable(t_node *node);
```
- TEXTTEXT

## main.c
```
static void	init_g_var(t_global g_var);
```
-  グローバル変数の構造体を初期化

```
static void	handle_line(char *line, int *stat_loc);
```
- tokenize->parse->expand->execの順にプロンプトに入力されたlineを実行していく。

```
int	main(void);
```
- テストでdiffをとるため、readlineの出力先をstderrに変更。

## parse_append.c
```
t_token	*tokdup(t_token *tok);
```
- TEXTTEXT

```
static void	append_tok(t_token **tok, t_token *elm);
```
- TEXTTEXT

```
static void	append_node(t_node **node, t_node *elm);
```
- TEXTTEXT

```
void	append_command_element(t_node *command, t_token **rest, t_token *tok);
```
- TEXTTEXT

## parse_redirect_op.c
```
- t_node	*redirect_out(t_token **rest, t_token *tok);
```
- TEXTTEXT

```
t_node	*redirect_in(t_token **rest, t_token *tok);
```
- TEXTTEXT

```
t_node	*redirect_append(t_token **rest, t_token *tok);
```
- TEXTTEXT

```
t_node	*redirect_heredoc(t_token **rest, t_token *tok);
```
- TEXTTEXT

## parse.c
```
bool	equal_op(t_token *tok, char *op);
```
- opが合っているか判定する

```
t_node	*new_node(t_node_kind kind);
```
-  新しいnodeを生成

```
static t_node	*simple_command(t_token **rest, t_token *tok);
```
- TEXTTEXT

```
t_node	*parse(t_token **rest, t_token *tok);
```
- TEXTTEXT

## signal_util.c
```
static void	handler(int signum)
```
- TEXTTEXT

```
void	reset_sig(int signum);
```
- TEXTTEXT

```
void	ignore_sig(int signum);
```
- TEXTTEXT

```
void	setup_sigint(void);
```
- TEXTTEXT

```
int		check_state(void);
```
- TEXTTEXT

## signal.c
```
void	setup_signal(void);
```
- TEXTTEXT

```
void	reset_signal(void);
```
- TEXTTEXT

## tokenize_is.c
```
bool	is_blank(char c);
```
- bashが定義するspaceかどうか判定

```
bool	is_metacharacter(char c);
```
- bashが定義するmetacharacterかnewlineかどうか判定

```
bool	is_word(const char *s);
```
- bashが定義するwordかどうか判定

```
bool	is_control_operator(t_token *tok);
```
- どのoperatorか判定

```
bool	is_eof(t_token *tok);
```
- 最後のtokか判定

## tokenize_word.c
```
static bool	word_single_quote(char **rest, char *line);
```
- wordがシングルクオートで囲まれている区間を読み飛ばす

```
static bool	word_double_quote(char **rest, char *line);
```
- wordがダブルクオートで囲まれている区間を読み飛ばす

```
t_token	*word(char **rest, char *line);
```
- bashが定義するwordに該当するものをtokとして返す

## tokenize.c
```
t_token	*new_token(char *word, t_token_kind kind);
```
- 新しいtokの生成

```
bool	check_op(const char *s, const char *keyword);
```
- operatorかどうか判定

```
static t_token	*operator(char **rest, char *line);
```
- bashが定義するcontrol operatorかredirectionに該当するものをtokとして返す

```
static bool	skip_blank(char **rest, char *line);
```
- lineのスペース、タブ、改行を読み飛ばす

```
t_token	*tokenize(char *line);
```
- lineをlistとして返す。listはtok構造体が連なっている
- tok構造体はmetacharacterかwordに分かれる
