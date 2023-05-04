/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:52 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 18:21:35 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_status;

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	setup_signal();
	g_last_status = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		interpret(line, &g_last_status);
		free(line);
	}
	exit(g_last_status);
}
// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
// system("leaks -q minishell");
// }
