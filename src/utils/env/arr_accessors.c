/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_accessors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:32:31 by egoh              #+#    #+#             */
/*   Updated: 2025/11/27 22:32:31 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

/**
 * @param env The env array
 * @param key The lookup key
 * @return A pointer to the value in the env array
 */
char	*get_env(t_array *env, const char *key)
{
	size_t	i;
	t_env	*item;

	if (!env || !key)
		return (NULL);
	i = 0;
	while (i < env->used_slots)
	{
		item = &env->data[i];
		if (item->key && !ft_strcmp(item->key, key))
			return (item->value);
		i++;
	}
	return (NULL);
}

bool	set_env(t_array *env, const char *key, const char *value)
{
	size_t	i;

	if (!env || !key)
		return (false);
	i = 0;
	while (i < env->used_slots)
	{
		if (env->data[i].key && !ft_strcmp(env->data[i].key, key))
		{
			if (env->data[i].value)
				free(env->data[i].value);
			if (value)
			{
				env->data[i].value = ft_strdup(value);
				if (!env->data[i].value)
					return (false);
			}
			else
				env->data[i].value = NULL;
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * Converts all the environment variables in the arguments
 * to their corresponding values. In the future we would
 * need to handle cases where the env variable is within
 * quotation marks to avoid converting them.
 */
bool	convert_all_env(t_ms *ms)
{
	size_t	i;
	char	*tmp;

	if (!ms || !ms->env || !ms->args)
		return (false);
	i = -1;
	while (ms->args[++i])
	{
		if (!is_env_var(ms->args[i], true))
			continue ;
		tmp = get_env(ms->env, ms->args[i] + 1);
		if (!tmp)
			continue ;
		tmp = ft_strdup(tmp);
		if (!tmp)
			return (false);
		free(ms->args[i]);
		ms->args[i] = tmp;
	}
	return (true);
}
