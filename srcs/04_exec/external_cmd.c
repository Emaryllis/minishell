/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:30:32 by julhong           #+#    #+#             */
/*   Updated: 2026/02/10 10:30:47 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * Formats evnp for execve from internal array of env kv-pairs
 * - rightly interprets env array as a spare (not dense arr)
 * - output evnp for execve is a dense array of char*
 */
static char	**format_envp(t_array *env)
{
	char	**envp;
	size_t	i;
	size_t	j;

	envp = malloc((env->used_slots + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	j = 0;
	i = -1;
	while (++i < env->used_slots)
	{
		if (env->data[i].key)
		{
			envp[j] = str3join(env->data[i].key, "=",
					env->data[i].value);
			if (!envp[j])
				return (free_2darr((void **)envp), NULL);
			j++;
		}
	}
	envp[j] = NULL;
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

static int	execve_abs(char *argv[], t_excmd v)
{
	if (stat(argv[0], &v.sst) != -1 && S_ISDIR(v.sst.st_mode))
		return (gen_perr(argv[0], "is a directory", MS_ER_NOTEXEC));
	if (execve(argv[0], argv, v.envp) == -1)
	{
		ft_printfd(2, NAME": %s: %s\n", argv[0], strerror(errno));
		if (errno == ENOENT || errno == ENOTDIR)
			return (MS_ER_CMDNOTF);
	}
	return (MS_ER_NOTEXEC);
}

static int	execve_rel(char *argv[], t_excmd v)
{
	int			exit_status;
	int			i;

	if (!v.path_arr)
		return (execve_abs(argv, v));
	i = -1;
	exit_status = MS_ER_CMDNOTF;
	while (v.path_arr[++i])
	{
		v.cmd_path = str3join(v.path_arr[i], "/", argv[0]);
		if ((access(v.cmd_path, F_OK) != 0
				|| (stat(v.cmd_path, &v.sst) != -1 && S_ISDIR(v.sst.st_mode)))
			&& (free(v.cmd_path), true))
			continue ;
		if (access(v.cmd_path, X_OK) != 0 && (free(v.cmd_path), true))
		{
			exit_status = MS_ER_NOTEXEC;
			continue ;
		}
		if (execve(v.cmd_path, argv, v.envp) == -1 && (free(v.cmd_path), true))
			break ;
	}
	return (ms_perr_exstat(argv[0], exit_status));
}

/**
 * Execute PATH command
 * - Formats env into char **evnp
 * - Sets input/output & closes fds
 * - Uses provided path or walks PATH with execve
 */
int	exc_ext_cmd(char *argv[], t_exctx ctx, t_msh *ms)
{
	t_excmd	var;
	int		exstat;

	ft_bzero(&var, sizeof(t_excmd));
	var.envp = format_envp(ms->env);
	if (!var.envp || dup2ctxstdio(ctx))
		return (ch_msh_clean(ctx, ms), EXIT_FAILURE);
	fd_clstwo(ctx.fdio);
	if (ft_strchr(argv[0], '/'))
		exstat = execve_abs(argv, var);
	else
	{
		var.path_arr = get_path_arr(ms->env);
		exstat = execve_rel(argv, var);
	}
	if (free_2darr((void **)var.envp), free_2darr((void **)var.path_arr), true)
		ch_msh_clean(ctx, ms);
	return (exstat);
}
