/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:29:19 by julhong           #+#    #+#             */
/*   Updated: 2025/12/19 18:58:24 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	walk_ast(t_ast *cur_node, t_msh *ms)
{
	pid_t	pid;

	if (cur_node->type == AST_CMD)
		msh_exec_cmd(cur_node->cmd_av, ms);
	else if (cur_node->type == AST_PIPE)
	{
		pipe(ms->fds.pipe_a);
		pid = fork();
		if (pid == 0)
		{
			//left sides pipe WR_END from fdout
			ms->fds.fdout = ms->fds.pipe_a[WR_END];
			walk_ast(cur_node->left, ms);
		}
		close(ms->fds.pipe_a[RE_END]);
		ms->fds.fdout = -1;
		pid = fork();
		if (pid == 0)
		{
			//right side pipe RE_END to fdin
			ms->fds.fdin = ms->fds.pipe_a[RE_END];
			walk_ast(cur_node->right, ms);
		}
		fd_cleanup(&ms->fds);
	}
}
