/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:08:37 by egoh              #+#    #+#             */
/*   Updated: 2026/02/08 02:42:04 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static char	*handle_tilde(t_msh *ms)
{
	char	*home;
	char	*result;

	home = get_env(ms->env, "HOME");
	if (!home)
		return (ft_printfd(2, NAME": cd: HOME not set\n"), NULL);
	result = malloc(ft_strlen(home) + ft_strlen(ms->args[1]) + 1);
	if (!result)
	{
		malloc_error(0);
		return (NULL);
	}
	ft_strcpy(result, home);
	ft_strcat(result, ms->args[1] + 1);
	return (result);
}

static char	*handle_env_target(t_msh *ms, char *key)
{
	char	*target;

	target = get_env(ms->env, key);
	if (!target)
		return (ft_printfd(2, NAME": cd: %s not set\n", key), NULL);
	target = ft_strdup(target);
	if (!target)
		return (malloc_error(0), NULL);
	return (target);
}

static char	*get_target_directory(t_msh *ms)
{
	char	*target;

	if (ms->args[1] && ms->args[2])
		return (ft_printfd(2, NAME": cd: too many arguments\n"), NULL);
	if (!ms->args[1] || ms->args[1][0] == '\0')
		target = handle_env_target(ms, "HOME");
	else if (!ft_strcmp(ms->args[1], "-"))
	{
		target = handle_env_target(ms, "OLDPWD");
		if (target)
			printf("%s\n", target);
	}
	else if (ms->args[1][0] == '~')
		target = handle_tilde(ms);
	else
	{
		target = ft_strdup(ms->args[1]);
		if (!target)
			return (malloc_error(0), NULL);
	}
	return (target);
}

/**
 * Set a new PWD or OLDPWD environment variable
 * If the variable doesn't exist, create it, then
 * push to env array.
 * If at any time malloc fails, return 1.
 * If env array fails to resize, output the
 * respective error messages and return 1.
 *
 * @param cwd current working dir
 * @param target target dir
 * @param type PWD or OLDPWD
 * @return 0 — success
 * @return 1 — failure
 */
static int	set_new_pwd(t_msh *ms, char *cwd, char *target, char *type)
{
	t_env		env;
	const int	code = set_env(ms->env, type, cwd);

	if (code == 0)
		return (handle_error(target, NAME": cd: malloc failed\n", NULL));
	if (code == 1)
		return (EXIT_SUCCESS);
	env = (t_env){ft_strdup(type), ft_strdup(cwd), false};
	if (!env.key || !env.value)
		return (free(env.key), free(env.value),
			handle_error(target, NAME": cd: malloc failed\n", NULL));
	if (!array_push(ms->env, env, true))
	{
		if (ft_strcmp(type, "PWD") == 0)
			return (free(env.key), free(env.value), handle_error(target,
					NAME": cd: failed to set PWD\n", NULL));
		if (ft_strcmp(type, "OLDPWD") == 0)
			return (free(env.key), free(env.value), handle_error(
					target, NAME": cd: failed to set OLDPWD\n", NULL));
	}
	return (EXIT_SUCCESS);
}

int	cell_cd(t_msh *ms)
{
	int		ret;
	char	*target;
	char	cwd[PATH_MAX];

	target = get_target_directory(ms);
	if (!target)
		return (EXIT_FAILURE);
	if (!getcwd(cwd, PATH_MAX))
		return (handle_error(target, "getcwd() error\n", NULL));
	ret = set_new_pwd(ms, cwd, target, "OLDPWD");
	if (ret != EXIT_SUCCESS)
		return (ret);
	if (chdir(target) != 0)
		return (handle_error(target, NULL, ms));
	if (!getcwd(cwd, PATH_MAX))
		return (handle_error(target, "getcwd() error\n", NULL));
	ret = set_new_pwd(ms, cwd, target, "PWD");
	if (ret != EXIT_SUCCESS)
		return (ret);
	free(target);
	return (EXIT_SUCCESS);
}
