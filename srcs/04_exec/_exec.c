/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:29:19 by julhong           #+#    #+#             */
/*   Updated: 2026/02/03 01:37:41 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/** Process diff AST nodes
 * - called recursively in handlers
 * - returns exstat
 */
int	proc_ast_node(t_ast *cur_node, t_exctx parent_ctx, t_msh *ms)
{
	if (cur_node->type == AST_CMD)
		return (exc_hdl_cmd(cur_node, parent_ctx, ms));
	else if (cur_node->type == AST_PIPE)
		return (exc_hdl_pipe(cur_node, parent_ctx, ms));
	else if (cur_node->type == AST_AND)
		return (exc_hdl_and(cur_node, parent_ctx, ms));
	else if (cur_node->type == AST_OR)
		return (exc_hdl_orr(cur_node, parent_ctx, ms));
	else if (cur_node->type == AST_SUBSH)
		return (exc_hdl_subsh(cur_node, parent_ctx, ms));
	return (0);
}

void	execute_ast(t_msh *ms)
{
	t_exctx	ctx;

	ctx.in_minsh = true;
	ctx.fdio[0] = -1;
	ctx.fdio[1] = -1;
	ms->exstat = proc_ast_node(ms->ast_root, ctx, ms);
	if (isatty(STDIN_FILENO) && (ms->exstat == 128 + SIGQUIT))
		ft_printfd(2, "Quit (Core dumped)\n");
	g_newsig = 0;
}
