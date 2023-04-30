# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 11:49:56 by snemoto           #+#    #+#              #
#    Updated: 2023/04/30 13:46:32 by snemoto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cleanup() {
	rm -f cmp out
	rm -f bash.txt minishell.txt
	rm -f a.out
	make fclean
}

assert() {
	printf '%-30s:' "\"$1\""
	
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

echo ---step4---
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'
assert 'a.out'
assert 'nosuchfile'

# echo "echo hoge" | ./minishell > minishell.txt
# echo "echo hoge" | bash > bash.txt
# diff minishell.txt bash.txt

# echo -e "cd ..\n pwd" | ./minishell > minishell.txt
# echo -e "cd ..\n pwd" | bash > bash.txt
# diff minishell.txt bash.txt

cleanup
echo 'all OK'
