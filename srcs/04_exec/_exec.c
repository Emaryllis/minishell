/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:30:32 by julhong           #+#    #+#             */
/*   Updated: 2025/12/19 01:27:19 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static char	*str3join(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	if (res)
		return (res);
	else
		return (NULL);
}

static char	**format_envp(t_array *env)
{
	char	**envp;
	size_t	i;

	envp = malloc((env->used_slots + 1) * sizeof(char *));
	if (!envp)
		return (malloc_fail_exit(), NULL);
	i = -1;
	while (++i < env->used_slots)
	{
		envp[i] = str3join(env->data[i].key, "=", env->data[i].value);
		if (!envp[i])
			return (malloc_fail_exit(), NULL);
	}
	envp[env->used_slots] = NULL;
	return (envp);
}

static char	**get_path_arr(t_array *env)
{
	char	*path_value;
	char	**path_arr;

	path_value = get_env(env, "PATH");
	if (path_value)
	{
		path_arr = ft_split(path_value, ':');
		return (path_arr);		
	}
	return (NULL);
}

/**
 * Execute PATH command
 * - Format env into char **evnp
 * - Set input/output
 * - walk PATH and try execve
 */
void	msh_exec_cmd(int fdin_out[2], char *argv[], t_msh *ms)
{
	char	**path_arr;
	char	**envp;
	char	*cmd_path;

	envp = format_envp(ms->env);

	//temp execve
	if (ft_strchr(argv[0], '/'))
	{
		execve(argv[0], argv, envp);
		//handle failure
	}
	path_arr = get_path_arr(ms->env);
	if (!path_arr)
		return ;
	for (int i = 0; path_arr[i]; i++)
	{
		cmd_path = str3join(path_arr[i], "/", argv[0]);
		execve(cmd_path, argv, envp);
		free(cmd_path);
	}


	// //set input / ouput
	// if (dup2(fdin_out[0], STDIN_FILENO) == -1
	// 	|| dup2(fdin_out[1], STDOUT_FILENO) == -1)
	// {
	// 	//handle error
	// }

	//execve through PATH
	
	//cleanup dump
	free (path_arr);
}