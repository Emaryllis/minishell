/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/19 01:21:40 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

void	cell_exec(t_ms *ms)
{
	if (!ft_strcmp(ms->args[0], "echo"))
		g_sig.status = cell_echo(ms);
	else if (!ft_strcmp(ms->args[0], "cd"))
		g_sig.status = cell_cd(ms);
	else if (!ft_strcmp(ms->args[0], "pwd"))
		g_sig.status = cell_pwd(ms);
	else if (!ft_strcmp(ms->args[0], "export"))
		g_sig.status = cell_export(ms);
	else if (!ft_strcmp(ms->args[0], "unset"))
		g_sig.status = cell_unset(ms);
	else if (!ft_strcmp(ms->args[0], "env"))
		g_sig.status = cell_env(ms);
	else if (!ft_strcmp(ms->args[0], "exit"))
		g_sig.status = cell_exit(ms);
	else
	{
		eprintf("%s: command not found\n", ms->args[0]);
		g_sig.status = 127;
	}
}
