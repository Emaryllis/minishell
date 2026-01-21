/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:10:21 by julhong           #+#    #+#             */
/*   Updated: 2026/01/21 23:36:35 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static bool	open_simple_rdr(t_redir *cur_redir, t_exctx *ctx, t_msh *ms)
{
	int	new_fd;
	int	*prev_fd;
	int	o_outtype;

	if (cur_redir->type == TK_RDR_IN)
	{
		prev_fd = &ctx->fdin;
		new_fd = open(cur_redir->target, O_RDONLY);
	}
	else
	{
		prev_fd = &ctx->fdout;
		o_outtype = O_TRUNC * (cur_redir->type == TK_RDR_OUT)
			+ O_APPEND * (cur_redir->type == TK_RDR_APND);
		new_fd = open(cur_redir->target, O_WRONLY | o_outtype | O_CREAT, 0644);
	}
	if (new_fd == -1)
	{
		ms->exit_status = ms_perr_exstat(cur_redir->target, 1);
		return (fd_cleanup(ctx), false);
	}
	fd_cls_set(prev_fd);
	*prev_fd = new_fd;
	return (true);
}

// Need to handle signals here
static void	heredoc(t_redir *cur_redir, t_exctx *ctx)
{
	int		pipe_hdoc[2];
	char	*limiter;
	int		lim_len;
	char	*line;

	pipe(pipe_hdoc);
	limiter = cur_redir->target;
	lim_len = ft_strlen(limiter);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, lim_len) == 0 && line[lim_len] == '\n')
		{
			free(line);
			get_next_line(-1);
			break ;
		}
		write(pipe_hdoc[1], line, ft_strlen(line));
		free(line);
	}
	fd_cls_set(&ctx->fdin);
	ctx->fdin = pipe_hdoc[0];
	close(pipe_hdoc[1]);
}

/**
 * Goes through and opens a cmd segment's redirs
 * @param cur_redir the cmd node's t_redir start ptr
 * @param ctx the cmd context to update as we go
 */
bool	run_redirs(t_redir *cur_redir, t_exctx *ctx, t_msh *ms)
{
	while (cur_redir)
	{
		if (cur_redir->type == TK_RDR_IN || cur_redir->type == TK_RDR_OUT
			|| cur_redir->type == TK_RDR_APND)
		{
			if (!open_simple_rdr(cur_redir, ctx, ms))
				return (false);
		}
		else
			heredoc(cur_redir, ctx);
		cur_redir = cur_redir->next;
	}
	return (true);
}
