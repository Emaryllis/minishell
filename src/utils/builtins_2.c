/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 07:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/19 03:34:24 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

int	cell_export(char **args)
{
	(void)args;
	return (EXIT_SUCCESS);
}

int	cell_unset(char **args)
{
	(void)args;
	return (EXIT_SUCCESS);
}

int	cell_env(char **args, char **envp)
{
	(void)args;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (EXIT_SUCCESS);
}

int	cell_exit(char **args)
{
	(void)args;
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	return (EXIT_SUCCESS);
}
