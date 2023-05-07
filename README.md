# minishell
The following is the file structure and function descriptions for minishell.

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
- __atribute__((noreturn)) を関数につけると、「この関数はreturnしない（≒この関数が呼ばれたときはプログラムが終了する）」ということをコンパイラに知らせることができる
- メモリ確保失敗などで利用

```
void	assert_error(const char *msg) __attribute__((noreturn));
```
- __atribute__((noreturn)) を関数につけると、「この関数はreturnしない（≒この関数が呼ばれたときはプログラムが終了する）」ということをコンパイラに知らせることができる
- シェルコマンドの不足などで利用

```
void	err_exit(const char *location, const char *msg, int status) __attribute__((noreturn));
```
- __atribute__((noreturn)) を関数につけると、「この関数はreturnしない（≒この関数が呼ばれたときはプログラムが終了する）」ということをコンパイラに知らせることができる
- シェルコマンドの不足などで利用（'location' command not found）

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
- 条件分岐によりheredoc中の変数、スペシャル変数（$?）を展開

```
int		read_heredoc(const char *delim, bool is_delim_unquoted);
```
- '<<'の後にreadlineを呼び出して読み込んでいく

## exec_pipe_prepare.c
```
static void	cpy_pipe(int dst[2], int src[2]);
```
- パイプのコピー

```
void	prepare_pipe(t_node *node);
```
- 与えられたノードがパイプ処理の出力先である場合、次のノードに対してパイプを準備
- 与えられたノードがパイプ処理の最後のノードである場合、何もしない
- pipeシステムコールを呼び出してパイプを作成し、次のノードの入力用パイプにコピー
- パイプ処理のための入力と出力の間にパイプを設定

```
void	prepare_pipe_child(t_node *node);
```
- 子プロセスがパイプを使用して標準入力と標準出力を切り替えるための準備
- 次のコマンドの標準出力をパイプでつながれた前のコマンドの標準入力にリダイレクトするための処理を行う

```
void	close_pipe(t_node *node);
```
- パイプを使ってコマンドをつなぐ際に、子プロセスが使用するパイプのファイルディスクリプタをクローズする

## exec_pipe.c
```
static void	validate_access(const char *path, const char *filename);
```
- pathが有効かどうか判定

```
static void	exec_child(t_node *node);
```
- 子プロセス内で、シグナル設定、fdの下準備、execveに与えるpath/argvの生成、execveによる実行を行う

```
static pid_t	exec_pipeline(t_node *node);
```
- fdの下準備を行い、子プロセスを生成

```
static int	wait_pipeline(pid_t last_pid);
```
- 最後に実行されたプロセスのPIDを受け取り、そのPIDのプロセスが終了するまで待機
- プロセスが終了すると、そのステータスを取得し、次のプロセスの実行のためにループが続く
- 全てのプロセスが終了した場合、関数はパイプラインの終了ステータスを返す
- 子プロセスの終了を待つ間にエラーが発生した場合、関数はエラーメッセージを出力して終了

```
int	expand_and_exec(t_node *node);
```
- 変数variable展開->quote削除の順にnodeを変更していく。
- nodeの種類kindに応じたリダイレクト処理、コマンドの実行を行う。

## exec_redirect_do_reset.c
```
bool	is_redirect(t_node *node);
```
- node->kindがリダイレクトかどうか判定

```
void	do_redirect(t_node *redir);
```
- targetfdを新しいnew_targetfdに変更
- filefdにtargetfdを割り当てる

```
void	reset_redirect(t_node *redir);
```
- 再帰的にnextの方からクローズしていく
- filefd, targetfdをクローズ
- new_targetfdにtargetfdを割り当てる

## exec_redirect_open.c
```
int		change_fd(int fd);
```
- 元のfdをクローズして、新しいfdを返す

```
static int	check_redir_file(t_node *node);
```
- node->kindに応じて、リダイレクトのfilefdをオープンしていく
- O_CREAT: ファイルが存在しない場合に、新規にファイルを作成することを指定します。
- O_TRUNC: ファイルがすでに存在する場合に、ファイルサイズを0に切り詰める
- O_APPENDは、ファイルの末尾に追記する
- '0644'は、6桁の8進数で表され、先頭の0は8進数であることを示す。所有者に読み書き権限、グループに読み取り権限、その他のユーザに読み取り権限を与える

```
int		open_redir_file(t_node *redir);
```
- node->kindに応じて、再帰的にnodeのfilefdをオープンしていく

## exec_search_path.c
```
static char	*check_path(const char *path);
```
- accessできればpathの文字列を生成して返す

```
char	*search_path(const char *filename);
```
- 環境変数PATHを取得して、引数filenameと組み合わせてaccessできるものを返す

## exec_token_to_argv.c
```
static char	**next_token(t_token *tok, int nargs, char **argv);
```
- 再帰的にtok->wordをargvに追記

```
char	**token_list_to_argv(t_token *tok);
```
- tokからargvを生成する

## expand_append.c
```
void	append_num(char **dst, unsigned int num);
```
- 数字を文字に変換して追記

```
void	append_char(char **s, char c);
```
- メモリを新たに確保して１文字追記

```
void	append_single_quote(char **dst, char **rest, char *p);
```
- シングルクオートで囲まれた文字列を追記

```
void	append_double_quote(char **dst, char **rest, char *p);
```
- ダブルクオートで囲まれた文字列を追記。
- 追記中に変数かスペシャル変数があるか確認。

## expand_is.c
```
bool	is_alpha_under(char c);
```
- アルファベットかアンダースコアか判定

```
bool	is_alpha_num_under(char c);
```
- アルファベットかアンダースコアか数字か判定

```
bool	is_variable(char *s);
```
- $に加えて、アルファベットかアンダースコアか判定

```
bool	is_special_parameter(char *s);
```
- スペシャル変数（$?）か判定

## expand_remove.c
```
static void	remove_single_quote(char **dst, char **rest, char *p);
```
- シングルクオートで囲まれた文字列をコピー

```
static void	remove_double_quote(char **dst, char **rest, char *p);
```
- ダブルクオートで囲まれた文字列をコピー

```
static void	remove_quote(t_token *tok);
```
- 条件分岐によりシングルクオート、ダブルクオートを除去

```
void	expand_quote_removal(t_node *node);
```
- 再帰的に全てのnodeのクオートを除去する

## expand_var.c
```
void	expend_special_parameter_str(char **dst, char **rest, char *p);
```
- newwordにステータス番号を代入

```
void	expand_variable_str(char **dst, char **rest, char *p);
```
- getenvを利用してnewwordに変数展開した内容を代入

```
static void	expand_variable_tok(t_token *tok);
```
- 条件分岐によりシングルクオート、ダブルクオート、変数、スペシャル変数（$?）を展開

```
void	expand_variable(t_node *node);
```
- 再帰的に全てのnodeの変数を展開する

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
- tok->wordを新たに生成

```
static void	append_tok(t_token **tok, t_token *elm);
```
- 最後のtokに新たなtok->wordを代入

```
static void	append_node(t_node **node, t_node *elm);
```
- 最後のnodeに新たなリダイレクトのノードを代入

```
void	append_command_element(t_node *command, t_token **rest, t_token *tok);
```
- tok->kindやリダイレクトの有無によって新たなtokenやnodeを生成

## parse_redirect_op.c
```
t_node	*redirect_out(t_token **rest, t_token *tok);
```
- '>'ノードを新たに生成

```
t_node	*redirect_in(t_token **rest, t_token *tok);
```
- '<'ノードを新たに生成

```
t_node	*redirect_append(t_token **rest, t_token *tok);
```
- '>>'ノードを新たに生成

```
t_node	*redirect_heredoc(t_token **rest, t_token *tok);
```
- '<<'ノードを新たに生成

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
static t_node	*new_command_node(t_token **rest, t_token *tok);
```
- 新しいnode->commandの生成

```
t_node	*parse(t_token **rest, t_token *tok);
```
- nodeを生成していく
- tokが'|'の場合は再帰的にparseを呼び出す。
- nodeのinpipe/outpipeを初期化

## signal_util.c
```
static void	handler(int signum)
```
- sigactionで呼び出されたら、グローバル変数にsignumを代入

```
void	reset_sig(int signum);
```
- シグナルハンドラをデフォルトの状態に戻すために使用
- 引数 signum は、リセットするシグナルの番号を指定
- 関数では、シグナルハンドラを SIG_DFL に設定しています。このフラグは、デフォルトのシグナル動作を指定
- sigaction 関数を使用して、シグナルの設定を変更
- sigemptyset 関数を使用して、シグナルハンドラによってマスクされたシグナルを解除し、sa_flags を 0 に設定して、既存のフラグを上書き

```
void	ignore_sig(int signum);
```
- 指定されたシグナル番号である signum のシグナルを無視するように設定するために使用
- シグナルの無視は、プログラムがそのシグナルを受け取っても、何も反応しないようにする
- 関数の中では、sigaction() 関数を呼び出して、シグナル signum に対するハンドラを設定
- sa_handler メンバーは SIG_IGN に設定されており、これはシグナルを無視する

```
void	setup_sigint(void);
```
- SIGINT (シグナル番号2) が発生したときに呼び出される関数 handler を登録するためのもの
- SIGINTは、Ctrl + Cキーが押されたときに送信されるシグナルで、通常はプログラムを中断するために使用
- 関数 sigaction() は、指定されたシグナルの振る舞いを設定します。この関数で、SIGINTに対して handler 関数を登録
- sa_mask フィールドは、シグナルハンドラの実行中にマスクされるシグナルのセットを指定します。ここでは、空のセットを指定しています
- sa_flags フィールドには、シグナルのオプションフラグを指定することができますが、ここでは0に設定

```
int		check_state(void);
```
- interruptedされたかどうかをモニタリング

## signal.c
```
void	setup_signal(void);
```
- readline ライブラリを使用してシェルのインタラクティブなモードをセットアップする
- _rl_echo_control_chars 変数を 0 に設定することで、入力されたコマンドのエコーバックを制御
- isatty(STDIN_FILENO) が真であれば rl_event_hook を check_state に設定して、readline ライブラリによる入力を受け付けるようにする
- isatty(STDIN_FILENO) は、標準入力がターミナルであるかどうか(プログラムが現在実行されているデバイスが、ユーザーが直接入出力を行うための端末であるかどうか)を判定
- SIGQUIT シグナルを無視する ignore_sig 関数と、SIGINT シグナルに対する setup_sigint 関数も呼び出す

```
void	reset_signal(void);
```
- シグナルハンドラが設定された後に、一時的にシグナルを無視するなどの処理が完了した後に、再びシグナルのデフォルト動作を復元するために使用
- SIGQUITとSIGINTのシグナルハンドラをシグナルのデフォルト値にリセット

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
