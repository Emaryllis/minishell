/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_mutators.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 05:00:49 by egoh              #+#    #+#             */
/*   Updated: 2025/12/30 14:24:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * Tries to insert data into empty slots if lazy is true.
 * @return true if successful, false otherwise.
 */
static bool	array_soft_push(t_array *arr, t_env elem, bool lazy)
{
	size_t	i;

	i = 0;
	while (i < arr->used_slots && lazy)
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

/**
 * Reallocates an array to a new capacity.
 * Essentially reallocarray, but:
 * - No overflow check for old_c * size and (new_c - old_c) * size
 * - Doesn't check for new_c == 0 and free ptr
 * - Does not zero new memory
 * - Newly allocated bytes are indeterminate
 * @param ptr The old pointer with information
 * @param old_c The old capacity
 * @param new_c The new capacity
 * @param size The size of each element
 * @return A new pointer with reallocated memory, or NULL on failure
 */
static void	*realloc_arr(void *ptr, size_t old_c, size_t new_c, size_t size)
{
	void	*new_ptr;

	if (new_c && SIZE_MAX / new_c < size)
		return (NULL);
	new_ptr = malloc(new_c * size);
	if (!new_ptr)
	{
		malloc_error(0);
		return (NULL);
	}
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_c * size);
		free(ptr);
	}
	if (new_c > old_c)
		ft_bzero((char *)new_ptr + old_c * size, (new_c - old_c) * size);
	return (new_ptr);
}

/**
 * Pushes [elem] to the end of the [arr] array.
 * @param arr The array to push to
 * @param elem The element to push
 * @param lazy If true, tries to fill empty slots first
 * @return true if successful, false otherwise
 */
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
			return (malloc_error(false));
		arr->data = tmp;
		arr->capacity = new_cap;
	}
	arr->data[arr->used_slots] = elem;
	arr->used_slots++;
	return (true);
}

/**
 * Removes a key value pair from the array.
 * @param arr The array to remove from
 * @param key The lookup key
 * @return true if successful, false otherwise
 */
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
