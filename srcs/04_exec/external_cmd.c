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

static int	rdy_set_execve(char *argv[], t_excmd var)
{
	int			exit_status;
	int			i;
	struct stat	sst;

	if (ft_strchr(argv[0], '/'))
	{
		if (stat(argv[0], &sst) != -1 && S_ISDIR(sst.st_mode))
			return (gen_perr(argv[0], "is a directory", MS_ER_NOTEXEC));
		if (execve(argv[0], argv, var.envp) == -1)
		{
			ft_printfd(2, NAME": %s: %s\n", argv[0], strerror(errno));
			if (errno == ENOENT || errno == ENOTDIR)
				return (MS_ER_CMDNOTF);
			return (MS_ER_NOTEXEC);
		}
	}
	if (!var.path_arr && execve(argv[0], argv, var.envp) == -1)
	{
		if (stat(argv[0], &sst) != -1 && S_ISDIR(sst.st_mode))
			return (gen_perr(argv[0], "is a directory", MS_ER_NOTEXEC));
		ft_printfd(2, NAME": %s: %s\n", argv[0], strerror(errno));
		if (errno == ENOENT || errno == ENOTDIR)
			return (MS_ER_CMDNOTF);
		return (MS_ER_NOTEXEC);
	}
	i = -1;
	exit_status = MS_ER_CMDNOTF;
	while (var.path_arr[++i])
	{
		var.cmd_path = str3join(var.path_arr[i], "/", argv[0]);
		if ((access(var.cmd_path, F_OK) != 0
				|| (stat(var.cmd_path, &sst) != -1 && S_ISDIR(sst.st_mode)))
			&& (free(var.cmd_path), true))
			continue ;
		if (access(var.cmd_path, X_OK) != 0 && (free(var.cmd_path), true))
		{
			exit_status = MS_ER_NOTEXEC;
			continue ;
		}
		if (execve(var.cmd_path, argv, var.envp) == -1
			&& (free(var.cmd_path), true))
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

	var.envp = format_envp(ms->env);
	if (!var.envp
		|| (ctx.fdio[0] != -1 && dup2(ctx.fdio[0], STDIN_FILENO) == -1)
		|| (ctx.fdio[1] != -1 && dup2(ctx.fdio[1], STDOUT_FILENO) == -1))
		return (ch_msh_clean(ctx, ms), EXIT_FAILURE);
	fd_clstwo(ctx.fdio);
	var.path_arr = get_path_arr(ms->env);
	exstat = rdy_set_execve(argv, var);
	free_2darr((void **)var.envp);
	free_2darr((void **)var.path_arr);
	ch_msh_clean(ctx, ms);
	return (exstat);
}
