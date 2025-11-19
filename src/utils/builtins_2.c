/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/19 20:08:47 by egoh             ###   ########.fr       */
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

int	cell_env(char **args, char **env)
{
	(void)args;
	while (*env)
		printf("%s\n", *env++);
	return (EXIT_SUCCESS);
}

int	cell_exit(char **args)
{
	(void)args;
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	return (EXIT_SUCCESS);
}
