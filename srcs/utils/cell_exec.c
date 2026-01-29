/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/01/29 15:52:23 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/** Only used in cell_cd */
int	handle_error(char *target, const char *format, t_msh *ms)
{
	char	*env;

	if (!ms)
	{
		ft_printfd(2, format);
		free(target);
		return (EXIT_FAILURE);
	}
	env = NULL;
	if (ms->args[1] && ms->env && ft_strcmp(ms->args[1], "-") == 0)
		env = get_env(ms->env, "OLDPWD");
	else if (ms->args[1] && ms->env && ft_strcmp(ms->args[1], "~") == 0)
		env = get_env(ms->env, "HOME");
	if (errno == EACCES)
		ft_printfd(2, NAME": cd: %s: Permission denied\n", target);
	else if (env)
		ft_printfd(2, NAME": cd: %s: No such file or directory\n", env);
	else if (ms->args[1])
		ft_printfd(2, NAME": cd: %s: No such file or directory\n", ms->args[1]);
	free(target);
	return (EXIT_FAILURE);
}

/**
 * Handles the execution of built-in commands
 * and the error message for unknown commands
 * as well as updating the status code.
 */
static void	handle_cell_exec(t_msh *ms, char *cmd)
{
	if (!ft_strcmp(ms->args[0], "echo"))
		ms->exstat = cell_echo(ms);
	else if (!ft_strcmp(ms->args[0], "cd"))
		ms->exstat = cell_cd(ms);
	else if (!ft_strcmp(ms->args[0], "pwd"))
		ms->exstat = cell_pwd(ms);
	else if (!ft_strcmp(ms->args[0], "export"))
		ms->exstat = cell_export(ms);
	else if (!ft_strcmp(ms->args[0], "unset"))
		ms->exstat = cell_unset(ms);
	else if (!ft_strcmp(ms->args[0], "env"))
		ms->exstat = cell_env(ms);
	else if (!ft_strcmp(ms->args[0], "exit"))
		ms->exstat = cell_exit(ms);
	else
	{
		ft_printfd(2, "%s: command not found\n", cmd);
		ms->exstat = 127;
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
