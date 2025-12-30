/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:08:37 by egoh              #+#    #+#             */
/*   Updated: 2025/12/30 14:24:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static char	*handle_tilde(t_msh *ms)
{
	char	*home;
	char	*result;

	home = get_env(ms->env, "HOME");
	if (!home)
		return (eprintf(NAME": cd: HOME not set\n"), NULL);
	if (ms->args[0][1] == '\0')
		return (ft_strdup(home));
	result = malloc(strlen(home) + strlen(ms->args[1]) + 1);
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
		return (eprintf(NAME": cd: %s not set\n", key), NULL);
	target = ft_strdup(target);
	if (!target)
		return (malloc_error(0), NULL);
	return (target);
}

static char	*get_target_directory(t_msh *ms)
{
	char	*target;

	if (ms->args[1] && ms->args[2])
		return (eprintf(NAME": cd: too many arguments\n"), NULL);
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

static int	set_new_pwd(t_msh *ms, char *cwd, char *target)
{
	char	*tmp;

	if (chdir(target) != 0)
		return (handle_error(target, NULL, ms));
	if (!getcwd(cwd, PATH_MAX))
		return (handle_error(target, "getcwd() error\n", NULL));
	if (!set_env(ms->env, "PWD", cwd))
	{
		tmp = ft_strdup(cwd);
		if (!tmp)
			return (handle_error(target, NAME": cd: malloc failed\n", NULL));
		if (!array_push(ms->env, (t_env){tmp, NULL}, true))
			return (handle_error(target, NAME": cd: failed to set PWD\n",
					NULL));
	}
	return (EXIT_SUCCESS);
}

int	cell_cd(t_msh *ms)
{
	int		ret;
	char	*tmp;
	char	*target;
	char	cwd[PATH_MAX];

	target = get_target_directory(ms);
	if (!target)
		return (EXIT_FAILURE);
	debug_print("%s", target);
	if (!getcwd(cwd, PATH_MAX))
		return (handle_error(target, "getcwd() error\n", NULL));
	ret = set_new_pwd(ms, cwd, target);
	if (ret != EXIT_SUCCESS)
		return (ret);
	if (!set_env(ms->env, "OLDPWD", cwd))
	{
		tmp = ft_strdup(cwd);
		if (!tmp)
			return (handle_error(target, NAME": cd: malloc failed\n", NULL));
		if (!array_push(ms->env, (t_env){tmp, NULL}, true))
			return (handle_error(target, NAME": cd: failed to set OLDPWD\n",
					NULL));
	}
	free(target);
	return (EXIT_SUCCESS);
}
