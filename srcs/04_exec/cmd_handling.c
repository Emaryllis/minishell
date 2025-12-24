/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:09:24 by julhong           #+#    #+#             */
/*   Updated: 2025/12/24 08:41:01 by julhong          ###   ########.fr       */
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
 * Goes through and opens a cmd segment's redirs
 * @param cur_redir the cmd node's t_redir start ptr
 * @param ctx the cmd context to update as we go
 */
void	run_redirs(t_redir *cur_redir, t_exctx *ctx)
{
	int	fd;

	if (cur_redir == NULL)
		return ;
	while (cur_redir)
	{
		if (cur_redir->type == TK_RDR_IN)
		{
			fd = open(cur_redir->target, O_RDONLY);
			if (fd == -1)
				{/*handle error*/}
			fd_cls_set(ctx->fdin);
			ctx->fdin = fd;
		}
		else if (cur_redir->type == TK_RDR_OUT)
			{/*handle*/}
		else if (cur_redir->type == TK_RDR_APND)
			{/*handle*/}
		else if (cur_redir->type == TK_RDR_HERE)
			{/*handle*/}
		cur_redir = cur_redir->next;
	}
}

void	exc_hdl_cmd(t_ast *cmd_node, t_exctx ctx, t_msh *ms)
{
	pid_t	pid;
	int		exstat;

	if (is_builtin(cmd_node->cmd_av[0]))
	{
		//save STD fds
		//apply redris if any
		ms->args = cmd_node->cmd_av;
		cell_exec(ms);
		fd_cleanup(&ctx);
		//restore STD fds
		exit(g_sig.status);
	}
	else //fork and run externally
	{
		pid = fork();
		if (pid == 0)
			exc_ext_cmd(cmd_node->cmd_av, ctx, ms);
		else if (pid == -1)
			exit(EXIT_FAILURE);
		fd_cleanup(&ctx);
		waitpid(pid, &exstat, 0);
		exit(interp_waitstat(exstat));
	}
}
