/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_mutators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 05:00:49 by egoh              #+#    #+#             */
/*   Updated: 2025/11/26 05:00:49 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static bool	array_soft_push(t_array *arr, t_env elem, bool lazy)
{
	size_t	i;

	i = 0;
	while (i < arr->capacity && lazy)
	{
		if (!arr->data[i].key)
		{
			arr->data[i] = elem;
			return (true);
		}
		i++;
	}
	return (false);
}

static void	*realloc_arr(void *ptr, size_t old_c, size_t new_c, size_t size)
{
	void	*new_ptr;

	if (new_c && SIZE_MAX / new_c < size)
		return (NULL);
	new_ptr = malloc(new_c * size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_c * size);
		free(ptr);
	}
	if (new_c > old_c)
		memset((char *)new_ptr + old_c * size, 0, (new_c - old_c) * size);
	return (new_ptr);
}

bool	array_push(t_array *arr, t_env elem, bool lazy)
{
	t_env	*tmp;
	size_t	new_cap;

	if (array_soft_push(arr, elem, lazy))
		return (true);
	if (arr->used_slots >= arr->capacity)
	{
		if (arr->capacity)
			new_cap = arr->capacity * 2;
		else
			new_cap = 2;
		tmp = realloc_arr(arr->data, arr->capacity, new_cap, sizeof(t_env));
		if (!tmp)
			return (false);
		arr->data = tmp;
		arr->capacity = new_cap;
	}
	arr->data[arr->used_slots] = elem;
	arr->used_slots++;
	return (true);
}

bool	array_remove(t_array *arr, char *key)
{
	size_t	i;
	t_env	*tmp;

	if (!arr || !key)
		return (true);
	i = 0;
	while (i < arr->used_slots)
	{
		tmp = &arr->data[i];
		if (tmp->key && !ft_strcmp(tmp->key, key))
		{
			free(tmp->key);
			free(tmp->value);
			tmp->key = NULL;
			tmp->value = NULL;
			return (true);
		}
		i++;
	}
	return (false);
}
