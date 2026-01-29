/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:29:19 by julhong           #+#    #+#             */
/*   Updated: 2026/01/30 00:13:37 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// static void	OLD_execute_ast(t_msh *ms)
// {
// 	t_ast	*root;
// 	t_exctx	ctx;
// 	pid_t	pid;
// 	int		wstat;

// 	root = ms->ast_root;
// 	// init_ctx(&ctx);
// 	if (root->type == AST_CMD && is_builtin(root->cmd_av[0]))
// 	{
// 		ms->args = expand_argv(root->cmd_av, root->cmd_ac, ms);
// 		debug_pr_fargv(ms->args);
// 		cell_exec(ms);
// 		free_2darr((void **)ms->args);
// 		ms->args = NULL;
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 			proc_ast_node(ms->ast_root, ctx, ms);
// 		else if (pid == -1)
// 		{
// 			ms->exstat = EXIT_FAILURE;
// 			return ;
// 		}
// 		waitpid(pid, &wstat, 0);
// 		ms->exstat = interp_wtstat(wstat);
// 	}
// }

void	execute_ast(t_msh *ms)
{
	t_exctx	ctx;

	ctx.in_minsh = true;
	ctx.in_subsh = false;
	ctx.fdin = -1;
	ctx.fdout = -1;
	ms->exstat = proc_ast_node(ms->ast_root, ctx, ms);
	if (isatty(STDIN_FILENO) && (ms->exstat == 128 + SIGQUIT))
		ft_printfd(2, "Quit (Core dumped)\n");
	g_newsig = 0;
}

int	proc_ast_node(t_ast *cur_node, t_exctx ctx, t_msh *ms)
{
	if (cur_node->type == AST_CMD)
		return (exc_hdl_cmd(cur_node, ctx, ms));
	// else if (cur_node->type == AST_PIPE)
	// 	exc_hdl_pipe(cur_node, ctx, ms);
	return (0);
}

// static void	exc_hdl_pipe(t_ast *cur_node, t_exctx ctx, t_msh *ms)
// {
// 	pid_t	left_pid;
// 	pid_t	right_pid;
// 	int		pipefds[2];
// 	t_exctx	left_ctx;
// 	t_exctx	right_ctx;
// 	int		wstat;

// 	ctx.is_piped = true;
// 	left_ctx = ctx;
// 	right_ctx = ctx;
// 	pipe(pipefds);
// 	left_ctx.fdout = pipefds[WR_END];
// 	left_pid = fork();
// 	if (left_pid == 0)
// 	{
// 		close(pipefds[RE_END]);
// 		proc_ast_node(cur_node->left, left_ctx, ms);
// 	}
// 	right_ctx.fdin = pipefds[RE_END];
// 	right_pid = fork();
// 	if (right_pid == 0)
// 	{
// 		close(pipefds[WR_END]);
// 		proc_ast_node(cur_node->right, right_ctx, ms);
// 	}
// 	close(pipefds[WR_END]);
// 	close(pipefds[RE_END]);
// 	waitpid(left_pid, NULL, 0);
// 	waitpid(right_pid, &wstat, 0);
// 	exit(interp_wtstat(wstat));
// }
