# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:49:56 by snemoto           #+#    #+#              #
#    Updated: 2023/05/04 16:16:27 by snemoto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

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

cleanup() {
	rm -f cmp out
	rm -f bash.txt minishell.txt
	rm -f a.out
	rm -f print_args
	make fclean
}

assert() {
	COMMAND="$1"
	shift
	printf '%-40s:' "[$COMMAND]"
	
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

echo ---step2---
assert ''

echo ---step3---
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

echo ---step4---
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'
assert 'a.out'
assert 'nosuchfile'

echo ---step5---
assert 'ls /'
assert 'echo hello	world	'
assert 'nosuchfile\n\n'
assert "./print_args 'hello	world' '42tokyo'"
assert "echo 'hello	world' '42tokyo'"
assert "echo '\"hello	world\"' '42tokyo'"
assert './print_args "hello	world" "42tokyo"'
assert 'echo "hello	world" "42tokyo"'
assert "echo \"'hello	world'\" \"42tokyo\""
assert "echo hello'	world'"
assert "echo hello'	world	'\"	42tokyo	\""

echo ---step9-1---
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'

echo ---step9-2---
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

echo ---step9-3---
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >> pwd.txt' 'pwd.txt'

echo ---step9-4---
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'

echo ---step10---
assert 'cat Makefile | grep minishell'
assert 'cat | cat | ls\n\n'

echo ---step11-1---
assert 'echo $USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER	$PATH	$TERM"'

echo ---finish---

cleanup
