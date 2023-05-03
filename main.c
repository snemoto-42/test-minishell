/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:52 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/03 13:46:40 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	t_token	*tok;
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$> ");
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			// // step2
			// interpret(line);
			// // step3
			// line = search_path(line);
			// interpret(line);
			// printf("line:%s\n", line);
			tok = tokenize(line);
			while (tok->kind != TK_EOF)
			{
			printf("word:%s\n", tok->word);
				tok = tok->next;
			}
			line = search_path(line);
			interpret(line);
		}
		free(line);
	}
	exit(EXIT_SUCCESS);
}

// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
// system("leaks -q minishell");
// }
