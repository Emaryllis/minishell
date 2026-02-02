/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_hndl_subsh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:27:45 by julhong           #+#    #+#             */
/*   Updated: 2026/02/03 01:34:50 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	exc_hdl_subsh(t_ast *cur_node, t_exctx ctx, t_msh *ms)
{
	pid_t	pid;
	int		subsh_exstat;
	int		wstat;

	pid = fork();
	if (pid == -1 && ch_msh_clean(ctx, ms))
		return (perror(NAME": fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		ctx.in_minsh = true;
		sigset_msh(0);
		sigset_generic(SIGINT, 0);
		if (!run_redirs(cur_node->redir_start, &ctx, ms)
			&& ch_msh_clean(ctx, ms))
			exit(EXIT_FAILURE);
		subsh_exstat = proc_ast_node(cur_node->left, ctx, ms);
		ctx.in_minsh = false;
		ch_msh_clean(ctx, ms);
		exit(subsh_exstat);
	}
	fd_clstwo(ctx.fdio);
	waitpid(pid, &wstat, 0);
	return (ch_msh_clean(ctx, ms), interp_wtstat(wstat));
}
