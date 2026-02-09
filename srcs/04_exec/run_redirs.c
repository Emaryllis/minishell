/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:10:21 by julhong           #+#    #+#             */
/*   Updated: 2026/02/07 17:03:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static char	**expand_target(char *target, t_msh *ms)
{
	char	*tmp_argv[2];
	char	**expd_rdr_tgt;

	tmp_argv[0] = target;
	tmp_argv[1] = NULL;
	expd_rdr_tgt = expand_argv(tmp_argv, 1, ms);
	if ((expd_rdr_tgt[1] != NULL) && ms_perr_exstat(target, MS_ER_AMBRDR))
		return (free_2darr((void **)expd_rdr_tgt), NULL);
	return (expd_rdr_tgt);
}

static void	hndl_hdoc(t_runrdr	*rr, t_redir *cur_redir, t_msh *ms)
{
	int	hd_raw_pfd;

	hd_raw_pfd = -1;
	if (cur_redir->hd_expans)
	{
		hd_raw_pfd = cur_redir->hd_pfd_0;
		heredoc_notatty(cur_redir, ms, cur_redir->hd_pfd_0);
		close(hd_raw_pfd);
	}
	rr->new_fd = cur_redir->hd_pfd_0;
	cur_redir->hd_pfd_0 = -1;
}

static void	hndl_out(t_runrdr	*rr, t_redir *cur_redir)
{
	rr->o_outtype = O_TRUNC * (cur_redir->type == TK_RDR_OUT)
		+ O_APPEND * (cur_redir->type == TK_RDR_APND);
	rr->new_fd = open(rr->expd_rdr_tgt[0], O_WRONLY | rr->o_outtype
			| O_CREAT, 0644);
}

static bool	rdr_ctx_proc(t_redir *cur_redir, t_exctx *ctx, t_msh *ms)
{
	t_runrdr	rr;

	if (cur_redir->type == TK_RDR_HERE)
		rr.expd_rdr_tgt = NULL;
	else
	{
		rr.expd_rdr_tgt = expand_target(cur_redir->target, ms);
		if (!rr.expd_rdr_tgt)
			return (false);
	}
	rr.prev_fd = &ctx->fdio[0];
	if (cur_redir->type == TK_RDR_IN)
		rr.new_fd = open(rr.expd_rdr_tgt[0], O_RDONLY);
	else if (cur_redir->type == TK_RDR_HERE)
		hndl_hdoc(&rr, cur_redir, ms);
	else
	{
		rr.prev_fd = &ctx->fdio[1];
		hndl_out(&rr, cur_redir);
	}
	if (rr.new_fd == -1)
		return (ms->exstat = ms_perr_exstat(rr.expd_rdr_tgt[0], 1)
			, free_2darr((void **)rr.expd_rdr_tgt), false);
	return (free_2darr((void **)rr.expd_rdr_tgt)
		, fd_clset(rr.prev_fd), *rr.prev_fd = rr.new_fd, true);
}

/**
 * Goes through and opens a cmd segment's redirs (if any)
 * - Params 
 * cur_redir the cmd node's t_redir start ptr
 * ctx the cmd context to update as we go
 * - Return
 * false if unable to open
 * true if OK
 */
bool	run_redirs(t_redir *cur_redir, t_exctx *ctx, t_msh *ms)
{
	while (cur_redir)
	{
		if (!rdr_ctx_proc(cur_redir, ctx, ms))
			return (false);
		cur_redir = cur_redir->next;
	}
	return (true);
}
