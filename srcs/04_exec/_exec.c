/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:29:19 by julhong           #+#    #+#             */
/*   Updated: 2025/12/30 23:00:48 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	interp_waitstat(int wstat)
{
	if (WIFEXITED(wstat))
		return (WEXITSTATUS(wstat));
	else if (WIFSIGNALED(wstat))
		return (128 + WTERMSIG(wstat));
	return (0);
}

static void	init_ctx(t_exctx *ctx)
{
	ft_bzero(ctx, sizeof(t_exctx));
	ctx->fdin = -1;
	ctx->fdout = -1;
}

void	execute_input(t_msh *ms)
{
	t_ast	*root;
	t_exctx	ctx;
	pid_t	pid;
	int		wstat;

	root = ms->ast_root;
	init_ctx(&ctx);
	if (root->type == AST_CMD && is_builtin(root->cmd_av[0]))
	{
		ms->args = dup_argv(root->cmd_av, root->cmd_ac);
		cell_exec(ms);
		free_2darr((void **)ms->args);
		ms->args = NULL;
	}
	else
	{
		pid = fork();
		if (pid == 0)
			walk_ast(ms->ast_root, ctx, ms);
		else if (pid == -1)
		{
			ms->exit_status = EXIT_FAILURE;
			return ;
		}
		waitpid(pid, &wstat, 0);
		ms->exit_status = interp_waitstat(wstat);
	}
}

static void	exc_hdl_pipe(t_ast *cur_node, t_exctx ctx, t_msh *ms)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		pipefds[2];
	t_exctx	left_ctx;
	t_exctx	right_ctx;
	int		wstat;

	ctx.is_piped = true;
	left_ctx = ctx;
	right_ctx = ctx;
	pipe(pipefds);
	left_ctx.fdout = pipefds[WR_END];
	left_pid = fork();
	if (left_pid == 0)
	{
		close(pipefds[RE_END]);
		walk_ast(cur_node->left, left_ctx, ms);
	}
	right_ctx.fdin = pipefds[RE_END];
	right_pid = fork();
	if (right_pid == 0)
	{
		close(pipefds[WR_END]);
		walk_ast(cur_node->right, right_ctx, ms);
	}
	close(pipefds[WR_END]);
	close(pipefds[RE_END]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &wstat, 0);
	exit(interp_waitstat(wstat));
}

void	walk_ast(t_ast *cur_node, t_exctx ctx, t_msh *ms)
{
	if (cur_node->type == AST_CMD)
		exc_hdl_cmd(cur_node, ctx, ms);
	else if (cur_node->type == AST_PIPE)
		exc_hdl_pipe(cur_node, ctx, ms);
}
