/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:06:27 by egoh              #+#    #+#             */
/*   Updated: 2025/12/30 14:24:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static int	same_dir(const char *a, const char *b)
{
	struct stat	sa;
	struct stat	sb;

	return (a && b && stat(a, &sa) == 0 && stat(b, &sb) == 0 && sa.st_ino
		== sb.st_ino && sa.st_dev == sb.st_dev);
}

char	*get_wd(t_msh *ms, char **cwd, bool p_err)
{
	char	*pwd;

	*cwd = NULL;
	pwd = get_env(ms->env, "PWD");
	if (pwd && pwd[0] == '/' && same_dir(pwd, "."))
		return (pwd);
	*cwd = getcwd(NULL, 0);
	if (*cwd)
		return (*cwd);
	if (p_err)
		perror("pwd: error retrieving current directory");
	return (NULL);
}

/**
 * Follows /bin/pwd builtin behavior
 */
//int	cell_pwd(t_msh *ms)
//{
//	char	*cwd;
//	char	*pwd;
//
//	pwd = get_wd(ms, &cwd, true);
//	if (!pwd)
//		return (EXIT_FAILURE);
//	printf("%s\n", pwd);
//	if (cwd)
//		free(cwd);
//	return (EXIT_SUCCESS);
//}

/**
 * Simpler version: bash's pwd builtin
 */
int	cell_pwd(t_msh *ms)
{
	char	*cwd;

	cwd = NULL;
	cwd = get_env(ms->env, "PWD");
	if (cwd && cwd[0] == '/')
	{
		printf("%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: error retrieving current directory");
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
