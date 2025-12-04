/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/12/04 23:03:33 by julhong          ###   ########.fr       */
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
		set_status(cell_echo(ms));
	else if (!ft_strcmp(ms->args[0], "cd"))
		set_status(cell_cd(ms));
	else if (!ft_strcmp(ms->args[0], "pwd"))
		set_status(cell_pwd(ms));
	else if (!ft_strcmp(ms->args[0], "export"))
		set_status(cell_export(ms));
	else if (!ft_strcmp(ms->args[0], "unset"))
		set_status(cell_unset(ms));
	else if (!ft_strcmp(ms->args[0], "env"))
		set_status(cell_env(ms));
	else if (!ft_strcmp(ms->args[0], "exit"))
		set_status(cell_exit(ms));
	else
	{
		eprintf("%s: command not found\n", cmd);
		set_status(127);
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
	if (!cmd || !convert_all_env(ms))
	{
		eprintf("Error parsing query... Exiting.");
		ms->exit = true;
		return ;
	}
	handle_cell_exec(ms, cmd);
	free(cmd);
}
