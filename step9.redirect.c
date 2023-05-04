/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step9.redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:26:26 by snemoto           #+#    #+#             */
/*   Updated: 2023/05/04 13:33:22 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	if (stashfd < 0)
		fatal_error("fcntl");
	if (close(fd) < 0)
		fatal_error("close");
	return (stashfd);
}

void	open_redir_file(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == ND_REDIR_OUT)
		redir->filefd = open(redir->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		todo("open_redir_file");
	redir->filefd = stashfd(redir->filefd);
	open_redir_file(redir->next);
}

void	do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (redir->kind == ND_REDIR_OUT)
	{
		redir->stashed_targetfd = stashfd(redir->targetfd);
		dup2(redir->filefd, redir->targetfd);		
	}
	do_redirect(redir->next);	
}

void	reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next);
	if (redir->kind == ND_REDIR_OUT)
	{
		close(redir->filefd);
		close(redir->targetfd);
		dup2(redir->stashed_targetfd, redir->targetfd);	
	}
}
