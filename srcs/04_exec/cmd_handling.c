/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:09:24 by julhong           #+#    #+#             */
/*   Updated: 2026/01/30 00:38:22 by julhong          ###   ########.fr       */
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

/**
 * Deep copies a char** (null terminated array of strings e.g. argv)
 * - copies up to ac arguments if AV is not not NULL
 * -- if ac is > argc then more space will be allocated beyond NULL
 * -- ac should be actual argc for exact copy
 * - if AV is NULL, then NULL will occupy dup[0]
 * -- space is allocated, but nothing is copied
 */
char	**dup_argv(char **av, int ac)
{
	char	**dup;
	int		i;

	dup = malloc((ac + 1) * sizeof(char *));
	i = 0;
	if (av)
	{
		while (av[i] && i < ac)
		{
			dup[i] = ft_strdup(av[i]);
			i++;
		}
	}
	dup[i] = NULL;
	return (dup);
}

/** Saves / Restores fd context for builtins in case of redirs
 * save_restore == 0 -> save
 * save_restore == 1 -> restore
 */
static bool	msh_fd_guard(int *ms_stdio, int save_restore)
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
			return (fd_cls_set(&ms_stdio[0]), false);
		return (true);
	}
	flag = true;
	if (dup2(ms_stdio[0], STDIN_FILENO) == -1)
		flag = false;
	if ((dup2(ms_stdio[1], STDOUT_FILENO) == -1))
		flag = false;
	fd_cls_set(&ms_stdio[0]);
	fd_cls_set(&ms_stdio[1]);
	return (flag);
}

int	exc_hdl_cmd(t_ast *cmd_node, t_exctx ctx, t_msh *ms)
{
	pid_t	pid;
	int		ms_stdio[2];
	int		wstat;

	ms->args = expand_argv(cmd_node->cmd_av, cmd_node->cmd_ac, ms);
	debug_pr_fargv(ms->args);
	if (is_builtin(ms->args[0]))
	{
		if (!msh_fd_guard(ms_stdio, 0))
			return (fd_cleanup(&ctx), EXIT_FAILURE);
		if (!run_redirs(cmd_node->redir_start, &ctx, ms)
			|| (ctx.fdin != -1 && dup2(ctx.fdin, STDIN_FILENO) == -1)
			|| (ctx.fdout != -1 && dup2(ctx.fdout, STDOUT_FILENO) == -1))
			return (fd_cleanup(&ctx), msh_fd_guard(ms_stdio, 1), EXIT_FAILURE);
		fd_cleanup(&ctx);
		cell_exec(ms);
		if (!msh_fd_guard(ms_stdio, 1))
			return (EXIT_FAILURE);
		return (ms->exstat);
	}
	else
	{
		pid = fork();
		if (pid == 0 && (sigset_child_dfl(), true))
		{
			if (!run_redirs(cmd_node->redir_start, &ctx, ms)
				&& (fd_cleanup(&ctx), true) && main_cleanup(ms))
				exit(EXIT_FAILURE);
			exit (exc_ext_cmd(ms->args, ctx, ms));
		}
		else if (pid == -1)
			return (perror(NAME": fork"), EXIT_FAILURE);
		fd_cleanup(&ctx);
		waitpid(pid, &wstat, 0);
		return (interp_wtstat(wstat));
	}
}
