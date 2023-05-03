# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:49:56 by snemoto           #+#    #+#              #
#    Updated: 2023/05/03 16:11:24 by snemoto          ###   ########.fr        #
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
	printf '%-40s:' "[$1]"
	
	echo -n -e "$1" | bash >cmp 2>&-
	expected=$?
	
	echo -n -e "$1" | ./minishell >out 2>&-
	actual=$?

	diff cmp out >/dev/null && echo -n '	diff OK' || echo -n '	diff NG'
	
	if [ "$actual" = "$expected" ]; then
		echo -n '	status OK'
	else
		echo -n "	status NG, expected $expected but got $actual"
	fi
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

cleanup
echo 'all OK'
