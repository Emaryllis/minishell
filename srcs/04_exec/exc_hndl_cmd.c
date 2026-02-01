/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_hndl_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:09:24 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 19:37:20 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

bool	is_builtin(char *argv0)
{
	if (!ft_strcmp(argv0, "echo"))
		return (true);
	else if (!ft_strcmp(argv0, "cd"))
		return (true);
	else if (!ft_strcmp(argv0, "pwd"))
		return (true);
	else if (!ft_strcmp(argv0, "export"))
		return (true);
	else if (!ft_strcmp(argv0, "unset"))
		return (true);
	else if (!ft_strcmp(argv0, "env"))
		return (true);
	else if (!ft_strcmp(argv0, "exit"))
		return (true);
	return (false);
}

/** Saves / Restores fd context for builtins in case of redirs
 * save_restore == 0 -> save
 * save_restore == 1 -> restore
 */
static bool	ms_fdgate(int *ms_stdio, int save_restore)
{
	bool	flag;

	if (save_restore == 0)
	{
		ms_stdio[0] = -1;
		ms_stdio[1] = -1;
		ms_stdio[0] = dup(STDIN_FILENO);
		if (ms_stdio[0] == -1)
			return (false);
		ms_stdio[1] = dup(STDOUT_FILENO);
		if (ms_stdio[1] == -1)
			return (fd_clset(&ms_stdio[0]), false);
		return (true);
	}
	flag = true;
	if (dup2(ms_stdio[0], STDIN_FILENO) == -1)
		flag = false;
	if ((dup2(ms_stdio[1], STDOUT_FILENO) == -1))
		flag = false;
	fd_clset(&ms_stdio[0]);
	fd_clset(&ms_stdio[1]);
	return (flag);
}

int	exc_hdl_cmd(t_ast *cmd_node, t_exctx ctx, t_msh *ms)
{
	pid_t	pid;
	int		ms_stdio[2];
	int		wstat;

	if (!ctx.in_minsh)
		fork_set_ch(&ctx, 0);
	ms->args = expand_argv(cmd_node->cmd_av, cmd_node->cmd_ac, ms);
	debug_pr_fargv(ms->args);
	if (!ms->args[0])
	{
		if (!run_redirs(cmd_node->redir_start, &ctx, ms))
			return (ch_msh_clean(ctx, ms), EXIT_FAILURE);
		return (ch_msh_clean(ctx, ms), EXIT_SUCCESS);
	}
	if (is_builtin(ms->args[0]))
	{
		if (!ms_fdgate(ms_stdio, 0))
			return (ch_msh_clean(ctx, ms), EXIT_FAILURE);
		if (!run_redirs(cmd_node->redir_start, &ctx, ms)
			|| (ctx.fdio[0] != -1 && dup2(ctx.fdio[0], STDIN_FILENO) == -1)
			|| (ctx.fdio[1] != -1 && dup2(ctx.fdio[1], STDOUT_FILENO) == -1))
			return (ch_msh_clean(ctx, ms), ms_fdgate(ms_stdio, 1)
				, EXIT_FAILURE);
		fd_clstwo(ctx.fdio);
		cell_exec(ms);
		if (!ms_fdgate(ms_stdio, 1))
			return (EXIT_FAILURE);
		return (ch_msh_clean(ctx, ms), ms->exstat);
	}
	else
	{
		pid = fork();
		if (pid == 0 && fork_set_ch(&ctx, 0))
		{
			if (!run_redirs(cmd_node->redir_start, &ctx, ms)
				&& ch_msh_clean(ctx, ms))
				exit(EXIT_FAILURE);
			exit(exc_ext_cmd(ms->args, ctx, ms));
		}
		else if (pid == -1 && ch_msh_clean(ctx, ms))
			return (perror(NAME": fork"), EXIT_FAILURE);
		fd_clstwo(ctx.fdio);
		waitpid(pid, &wstat, 0);
		return (ch_msh_clean(ctx, ms), interp_wtstat(wstat));
	}
}
