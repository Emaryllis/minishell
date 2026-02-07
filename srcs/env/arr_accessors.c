/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_accessors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:32:31 by egoh              #+#    #+#             */
/*   Updated: 2026/02/08 03:11:21 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * @param env The env array
 * @param key The lookup key
 * @return A pointer to the value in the env array
 * @return NULL if it does not exist
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

/** Sets env for if that key already exists
 * @param env The env array
 * @param key The lookup key
 * @param value The new value to set
 * @return 1 — success
 * @return 0 — malloc error
 * @return -1 — nonexistent key
 */
int	set_env(t_array *env, const char *key, const char *value)
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
			env->data[i].is_nul = value == NULL;
			if (!value)
			{
				env->data[i].value = NULL;
				return (1);
			}
			env->data[i].value = ft_strdup(value);
			if (!env->data[i].value)
				return (malloc_error(0));
			return (1);
		}
		i++;
	}
	return (-1);
}
