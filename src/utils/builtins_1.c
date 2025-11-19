/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/19 19:32:54 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static int	is_n_flag(const char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	if (arg[i] == '\0')
		return (0);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	cell_echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	cell_cd(char **args)
{
	(void)args;
	return (EXIT_SUCCESS);
}

int	cell_pwd(char **args)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	(void)args;
	pwd = getenv("PWD");
	if (pwd && pwd[0] == '/')
	{
		printf("%s\n", pwd);
		return (EXIT_SUCCESS);
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
