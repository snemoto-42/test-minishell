/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:52 by snemoto           #+#    #+#             */
/*   Updated: 2023/04/30 13:42:54 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	// rl_outstream = stderr;
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
			interpret(search_path(line));
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
