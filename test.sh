# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:49:56 by snemoto           #+#    #+#              #
#    Updated: 2023/05/14 13:46:14 by snemoto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char **argv) {
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = %s\n", i, argv[i]);
}
EOF

cat <<EOF | gcc -xc -o exit42 -
int main() { return 42; }
EOF

print_desc(){
		echo -e $YELLOW"$1"$RESET
}

cleanup() {
	rm -f 	cmp out
	rm -f	bash.txt		
	rm -f	minishell.txt	
	rm -f	a.out			
	rm -f	print_args		
	rm -f	exit42			
	rm -f	infinite_loop	
	rm -f	no_exec_perm	
	rm -f	no_read_perm
	make fclean
}

assert() {
	COMMAND="$1"
	shift
	printf '%-75s:' "[$COMMAND]"
	
	echo -n -e "$COMMAND" | bash >cmp 2>&-
	expected=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".cmp"
	done

	echo -n -e "$COMMAND" | ./minishell >out 2>&-
	actual=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".out"
	done

	diff cmp out >/dev/null && echo -n "	diff OK" || echo -n "	diff NG"
	
	if [ "$actual" = "$expected" ]; then
		echo -n "	status OK"
	else
		echo -n "	status NG, expected $expected but got $actual"
	fi
	for arg in "$@"
	do
		echo -n " [$arg] "
		diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
		rm -f "$arg"".cmp" "$arg"".out"
	done
	echo
}

make all

assert ''

assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'
assert 'a.out'
assert 'nosuchfile'

assert 'ls /'
assert 'echo hello     world     '
assert 'nosuchfile\n\n'
assert "./print_args 'hello   world'    '42tokyo'"
assert "echo 'hello   world' '42tokyo'"
assert "echo '\"hello     world\"' '42tokyo'"
assert './print_args "hello    world" "42tokyo"'
assert 'echo "hello   world" "42tokyo"'
assert "echo \"'hello    world'\" \"42tokyo\""
assert "echo hello'   world'"
assert "echo hello'   world  '\"  42tokyo   \""

assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >> pwd.txt' 'pwd.txt'

assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'

assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'

assert 'echo $USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER   $PATH    $TERM"'

assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'

assert 'cat <<EOF \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
export EOF="eof"
assert 'cat <<$EOF \neof\nEOF\nEOF'
assert 'cat <<"$EOF" \neof\nEOF\nEOF'

echo "int main() { while(1) ; }" | gcc -xc -o infinite_loop -

print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null

print_desc "SIGQUIT to SHELL"
(sleep 0.01; pkill -SIGQUIT bash;
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGQUIT minishell
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null

print_desc "SIGINT to SHELL"
(sleep 0.01; pkill -SIGINT bash;
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGINT minishell
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null

print_desc "SIGTERM to child process"
(sleep 0.01; pkill -SIGTERM infinite_loop;
 sleep 0.01; pkill -SIGTERM infinite_loop) &
assert './infinite_loop'

print_desc "SIGINT to child process"
(sleep 0.01; pkill -SIGINT infinite_loop;
 sleep 0.01; pkill -SIGINT infinite_loop) &
assert './infinite_loop'

print_desc "SIGQUIT to child process"
(sleep 0.01; pkill -SIGQUIT infinite_loop;
 sleep 0.01; pkill -SIGQUIT infinite_loop) &
assert './infinite_loop'

print_desc "SIGINT to child process"
(sleep 0.01; pkill -SIGUSR1 infinite_loop;
 sleep 0.01; pkill -SIGUSR1 infinite_loop) &
assert './infinite_loop'

# Manual Debug
# $ ./minishell
# $ 
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ hogehoge
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# >
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# > hoge
# > fuga
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D

assert	'exit'
assert	'exit 42'
assert	'exit ""'
assert	'exit hello'
assert	'exit 42tokyo'
assert	'exit 1 2'

print_desc "Output of 'export' differs, but it's ok."
assert	'export'
assert	'export | grep nosuch | sort'
assert	'export nosuch\n export | grep nosuch | sort'
assert	'export nosuch=fuga\n export | grep nosuch | sort'
assert	'export nosuch=fuga hoge=nosuch\n export | grep nosuch | sort'
assert	'export [invalid]'
assert	'export [invalid_nosuch]\n export | grep nosuch | sort'
assert	'export [invalid]=nosuch\n export | grep nosuch | sort'
assert	'export [invalid] nosuch hoge=nosuch\n export | grep nosuch | sort'
assert	'export nosuch [invalid] hoge=nosuch\n export | grep nosuch | sort'
assert	'export nosuch hoge=nosuch [invalid]\n export | grep nosuch | sort'
assert	'export nosuch="nosuch2=hoge\n"export $nosuch export | grep nosuch | sort'

export hoge fuga=fuga
assert	'unset'
assert	'unset hoge'
assert	'unset fuga'
assert	'unset nosuch'
assert	'unset [invalid]'
assert	'unset hoge fuga'
assert	'unset hoge nosuch fuga'
assert	'unset fuga \n export | echo '$fuga''
assert	'unset [invalid] fuga \n echo $fuga'

print_desc "Output of 'env' differs, but it's ok."
assert	'env'
assert	'env | grep hoge | sort'

assert	'cd'
assert	'cd .'
assert	'cd ..'
assert	'cd ///'
assert	'cd /tmp'
assert	'cd /tmp///'
assert	'cd /../../../././.././'
assert	'cd obj'
assert	'unset HOME\ncd'
assert	'cd \n echo $PWD'
assert	'cd \n echo $PWD'
assert	'cd .\n echo $PWD'
assert	'cd ..\n echo $PWD'
assert	'cd ///\n echo $PWD'
assert	'cd /tmp/\n echo $PWD'
assert	'cd /tmp///\n echo $PWD'
assert	'cd /../../../././.././\n echo $PWD'
assert	'cd obj\n echo $PWD'
assert	'unset HOME\ncd \n echo $PWD'

assert	'echo'
assert	'echo hello'
assert	'echo hello " " world'
assert	'echo -n'
assert	'echo -n hello'
assert	'echo -n hello world'
assert	'echo hello -n'

assert	'pwd'
assert	'cd\npwd'
assert	'cd obj\npwd'
assert	'cd /etc\npwd'
assert	'cd . \n pwd \n echo $PWD $OLDPWD'
assert	'cd .. \n pwd \n echo $PWD $OLDPWD'
assert	'cd /// \n pwd \n echo $PWD $OLDPWD'
assert	'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
assert	'unset PWD\npwd\ncd /etc/\npwd'

cleanup
