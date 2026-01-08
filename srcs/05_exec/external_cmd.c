/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:30:32 by julhong           #+#    #+#             */
/*   Updated: 2026/01/06 02:31:50 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

char	*str3join(const char *s1, const char *s2, const char *s3)
{
	int		ttl_len;
	char	*res_str;

	ttl_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	res_str = malloc(ttl_len + 1);
	if (!res_str)
		return (NULL);
	res_str[0] = '\0';
	ft_strcpy(res_str, s1);
	ft_strcat(res_str, s2);
	ft_strcat(res_str, s3);
	return (res_str);
}

static char	**format_envp(t_array *env)
{
	char	**envp;
	size_t	i;

	envp = malloc((env->used_slots + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	i = -1;
	while (++i < env->used_slots)
	{
		envp[i] = str3join(env->data[i].key, "=", env->data[i].value);
		if (!envp[i])
			return (NULL);
	}
	envp[env->used_slots] = NULL;
	return (envp);
}

static char	**get_path_arr(t_array *env)
{
	char	*path_value;
	char	**path_arr;

	path_value = get_env(env, "PATH");
	if (!path_value)
		return (NULL);
	path_arr = ft_split(path_value, ':');
	return (path_arr);
}

static void	rdy_set_execve(char *argv[], t_excmd var)
{
	int		exit_status;
	int		i;

	if (ft_strchr(argv[0], '/') && execve(argv[0], argv, var.envp) == -1)
	{
		if (errno == ENOENT)
			exit(MS_ER_CMDNOTF);
		exit(MS_ER_NOTEXEC);
	}
	i = -1;
	exit_status = MS_ER_CMDNOTF;
	while (var.path_arr[++i])
	{
		var.cmd_path = str3join(var.path_arr[i], "/", argv[0]);
		if (!var.cmd_path)
			exit(EXIT_FAILURE);
		if (execve(var.cmd_path, argv, var.envp) == -1)
		{
			free(var.cmd_path);
			if (errno != ENOENT)
				exit_status = MS_ER_NOTEXEC;
			continue ;
		}
	}
	exit(exit_status);
}

/**
 * Execute PATH command
 * - Formats env into char **evnp
 * - Sets input/output & closes fds
 * - Uses provided path or walks PATH with execve
 */
void	exc_ext_cmd(char *argv[], t_exctx ctx, t_msh *ms)
{
	t_excmd	var;

	var.envp = format_envp(ms->env);
	if (!var.envp
		|| (ctx.fdin != -1 && dup2(ctx.fdin, STDIN_FILENO) == -1)
		|| (ctx.fdout != -1 && dup2(ctx.fdout, STDOUT_FILENO) == -1))
		return (fd_cleanup(&ctx), exit(EXIT_FAILURE));
	fd_cleanup(&ctx);
	var.path_arr = get_path_arr(ms->env);
	if (!var.path_arr)
		exit(MS_ER_CMDNOTF);
	rdy_set_execve(argv, var);
}
