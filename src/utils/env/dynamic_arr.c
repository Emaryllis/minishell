/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 03:25:27 by egoh              #+#    #+#             */
/*   Updated: 2025/11/26 03:25:27 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static bool	split_env(const char *str, char **key, char **value)
{
	const char	*equal = ft_strchr(str, '=');

	if (!equal)
	{
		*key = ft_strdup(str);
		if (!*key)
			return (false);
		*value = NULL;
		return (true);
	}
	*key = ft_strndup(str, equal - str);
	if (!*key)
		return (false);
	*value = ft_strdup(equal + 1);
	if (!*value)
	{
		free(*key);
		*key = NULL;
		return (false);
	}
	return (true);
}

void	array_free(t_array *arr)
{
	size_t	i;

	if (!arr || !arr->data)
		return ;
	i = 0;
	while (i < arr->used_slots)
	{
		if (arr->data[i].key)
			free(arr->data[i].key);
		if (arr->data[i].value)
			free(arr->data[i].value);
		i++;
	}
	free(arr->data);
	arr->data = NULL;
	arr->used_slots = 0;
	arr->capacity = 0;
}

bool	init_array(t_array *arr, char **data)
{
	size_t	i;
	t_env	item;

	i = 0;
	arr->used_slots = 0;
	arr->capacity = 2;
	arr->data = ft_calloc(arr->capacity, sizeof(t_env));
	if (!arr->data)
		return (false);
	while (data[i])
	{
		if (!split_env(data[i], &item.key, &item.value))
			return (array_free(arr), false);
		if (!array_push(arr, item, false))
		{
			free(item.key);
			free(item.value);
			return (array_free(arr), false);
		}
		i++;
	}
	return (true);
}
