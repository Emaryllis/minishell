/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:06:27 by egoh              #+#    #+#             */
/*   Updated: 2026/02/13 01:07:05 by julhong          ###   ########.fr       */
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
 * Idk why but it seems to check if env PWD is set
 * & valid dir, then tries to getcwd if it fails...
 * Then it prints PWD if it isn't empty?
 */
int	cell_pwd(t_msh *ms)
{
	char	*cwd;
	char	*wd;

	wd = get_wd(ms, &cwd, false);
	if (!wd)
		wd = get_env(ms->env, "PWD");
	if (wd)
	{
		if (ft_printf("%s\n", wd) == -1)
			return (perror(NAME": write error"), EXIT_FAILURE);
	}
	if (cwd)
		free(cwd);
	return (EXIT_SUCCESS);
}
