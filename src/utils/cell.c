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

t_st	cell_exec(char **args, char **env)
{
	if (!ft_strcmp(args[0], "echo"))
		return ((t_st){cell_echo(args), false});
	else if (!ft_strcmp(args[0], "cd"))
		return ((t_st){cell_cd(args), false});
	else if (!ft_strcmp(args[0], "pwd"))
		return ((t_st){cell_pwd(args), false});
	else if (!ft_strcmp(args[0], "export"))
		return ((t_st){cell_export(args), false});
	else if (!ft_strcmp(args[0], "unset"))
		return ((t_st){cell_unset(args), false});
	else if (!ft_strcmp(args[0], "env"))
		return ((t_st){cell_env(args, env), false});
	else if (!ft_strcmp(args[0], "exit"))
		return ((t_st){cell_exit(args), true});
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return ((t_st){127, false});
}
