/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/01/18 02:09:44 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * Handles the execution of built-in commands
 * and the error message for unknown commands
 * as well as updating the status code.
 */
static void	handle_cell_exec(t_msh *ms, char *cmd)
{
	if (!ft_strcmp(ms->args[0], "echo"))
		ms->exit_status = cell_echo(ms);
	else if (!ft_strcmp(ms->args[0], "cd"))
		ms->exit_status = cell_cd(ms);
	else if (!ft_strcmp(ms->args[0], "pwd"))
		ms->exit_status = cell_pwd(ms);
	else if (!ft_strcmp(ms->args[0], "export"))
		ms->exit_status = cell_export(ms);
	else if (!ft_strcmp(ms->args[0], "unset"))
		ms->exit_status = cell_unset(ms);
	else if (!ft_strcmp(ms->args[0], "env"))
		ms->exit_status = cell_env(ms);
	else if (!ft_strcmp(ms->args[0], "exit"))
		ms->exit_status = cell_exit(ms);
	else
	{
		ft_printfd(2, "%s: command not found\n", cmd);
		ms->exit_status = 127;
	}
}

/**
 * Handles the execution of built-in commands.
 * Uses a duplicate of the command name to
 * avoid displaying a garbage value if the
 * first argument is a valid env key.
 * @see handle_cell_exec
 */
void	cell_exec(t_msh *ms)
{
	char	*cmd;

	cmd = ft_strdup(ms->args[0]);
	if (!cmd)
	{
		ft_printfd(2, "Error parsing query... Exiting.");
		ms->shell_exit = true;
		return ;
	}
	handle_cell_exec(ms, cmd);
	free(cmd);
}
