/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_accessors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:32:31 by egoh              #+#    #+#             */
/*   Updated: 2026/01/06 16:07:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

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
					return (malloc_error(false));
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
 * Converts simple env var str to corresponding value
 *
 * Notes:
 * - simple env var str == entire string is the env variable
 * - function only works in conjunction with convert_all_env
 */
static char	*get_value(t_msh *ms, size_t i, bool *cont)
{
	char	*tmp;

	if (!is_env_var(ms->args[i], true))
	{
		if (!ft_strcmp(ms->args[i], "$?"))
			return (ft_itoa(g_sig.status));
		*cont = true;
	}
	else
	{
		tmp = get_env(ms->env, ms->args[i] + 1);
		if (tmp)
			return (ft_strdup(tmp));
		return (ft_strdup(""));
	}
	return (NULL);
}

/**
 * Converts any simple env var str entries in argv array to corresponding values
 * 
 * Notes:
 * - simple env var str == entire string is the env variable
 */
bool	convert_all_env(t_msh *ms)
{
	size_t	i;
	char	*tmp;
	bool	cont;

	if (!ms || !ms->env || !ms->args)
		return (false);
	i = -1;
	cont = false;
	while (ms->args[++i])
	{
		tmp = get_value(ms, i, &cont);
		if (cont)
		{
			cont = false;
			continue ;
		}
		if (!tmp)
			return (malloc_error(false));
		free(ms->args[i]);
		ms->args[i] = tmp;
	}
	return (true);
}
