/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:10:21 by julhong           #+#    #+#             */
/*   Updated: 2026/01/22 16:05:00 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static bool	ctx_rdr_proc(t_redir *cur_redir, t_exctx *ctx, t_msh *ms)
{
	int	new_fd;
	int	*prev_fd;
	int	o_outtype;

	prev_fd = &ctx->fdin;

	if (cur_redir->type == TK_RDR_IN)
		new_fd = open(cur_redir->target, O_RDONLY);
	else if (cur_redir->type == TK_RDR_HERE)
		new_fd = cur_redir->hdoc_pipefd_0;
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

/**
 * Goes through and opens a cmd segment's redirs
 * - Params 
 * cur_redir the cmd node's t_redir start ptr
 * ctx the cmd context to update as we go
 * 
 * - Notes
 * Heredoc resolution to be moved to parsing stage
 * Handling of hdoc type redir can be a var or mod of open simople rdr
 * 
 */
bool	run_redirs(t_redir *cur_redir, t_exctx *ctx, t_msh *ms)
{
	while (cur_redir)
	{
		if (!ctx_rdr_proc(cur_redir, ctx, ms))
			return (false);
		cur_redir = cur_redir->next;
	}
	return (true);
}
