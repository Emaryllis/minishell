/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 17:09:24 by julhong           #+#    #+#             */
/*   Updated: 2025/12/30 22:55:18 by julhong          ###   ########.fr       */
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

char	**dup_argv(char **av, int ac)
{
	char	**exc_argv;
	int		i;

	exc_argv = malloc((ac + 1) * sizeof(char *));
	i = -1;
	while (++i < ac)
		exc_argv[i] = ft_strdup(av[i]);
	exc_argv[ac] = NULL;
	return (exc_argv);
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
		{
			if (!run_redirs(cmd_node->redir_start, &ctx, ms))
				exit(EXIT_FAILURE);	
			exc_ext_cmd(cmd_node->cmd_av, ctx, ms);
		}
		else if (pid == -1)
			exit(EXIT_FAILURE);
		fd_cleanup(&ctx);
		waitpid(pid, &exstat, 0);
		exit(interp_waitstat(exstat));
	}
}
