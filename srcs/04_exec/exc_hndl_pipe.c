/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_hndl_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:51:18 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 01:58:12 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	pipe_setio(t_chio *ch, t_exctx p_ctx, t_ast *cur_node, int pfds[2])
{
	if ("left" && true)
	{
		ch->ctx[CH_LFT] = p_ctx;
		ch->ctx[CH_LFT].fdio[WR_END] = pfds[WR_END];
		ch->node[CH_LFT] = cur_node->left;
	}
	if ("right" && true)
	{
		ch->ctx[CH_RHT] = p_ctx;
		ch->ctx[CH_RHT].fdio[RE_END] = pfds[RE_END];
		ch->node[CH_RHT] = cur_node->right;
	}
}

/** Handle pipes
 * - 1 of 2 forking points (other cmd/subshell)
 * - calls proc_ast_node recursively on forked children
 * 
 * Returning recursively the right way~
 * - children exit on proc_ast_node
 * - pipe waits and collects RHT exstat
 */
int	exc_hdl_pipe(t_ast *cur_node, t_exctx p_ctx, t_msh *ms)
{
	int		i;
	int		pfds[2];
	t_chio	ch;

	if (pipe(pfds) == -1 && ch_msh_clean(p_ctx, ms))
		return (perror(NAME": pipe"), EXIT_FAILURE);
	pipe_setio(&ch, p_ctx, cur_node, pfds);
	i = -1;
	while (++i < 2)
	{
		ch.pid[i] = fork();
		if (ch.pid[i] == -1 && fd_clstwo(pfds) && ch_msh_clean(p_ctx, ms))
		{
			if (i == CH_RHT)
				waitpid(ch.pid[CH_LFT], NULL, 0);
			return (perror(NAME": fork"), EXIT_FAILURE);
		}
		if (ch.pid[i] == 0 && fd_clset(&pfds[i]) && fork_set_ch(&ch.ctx[i]))
		{
			if (i == CH_LFT)
				fd_clset(&p_ctx.fdio[WR_END]);
			else
				fd_clset(&p_ctx.fdio[RE_END]);
			exit(proc_ast_node(ch.node[i], ch.ctx[i], ms));
		}
	}
	fd_clstwo(pfds);
	waitpid(ch.pid[CH_LFT], NULL, 0);
	return (waitpid(ch.pid[CH_RHT], &ch.wstat, 0), interp_wtstat(ch.wstat));
}
