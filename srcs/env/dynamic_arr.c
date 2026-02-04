/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 03:25:27 by egoh              #+#    #+#             */
/*   Updated: 2026/02/04 20:35:44 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/**
 * Checks and extracts the key from the environment string.
 * If there is no '=' character, it treats the entire string as the key.
 * It will return false & free key if:
 * - The key is not a valid environment variable name. (see {is_env_var})
 * - Memory allocation fails.
 * @param str The string to check.
 * @param key Pointer to store the allocated key string.
 * @param value Pointer to store the allocated value string.
 * @param equal Pointer to the '=' character in the string, or NULL if not found.
 * @return 1 if successful, 0 if memory allocation fails,
 * -1 if the key is not a valid environment variable name.
 * @see is_env_var
 */
static int	check_env_key(const char *str, char **key, char **value,
							const char *equal)
{
	if (!equal)
	{
		if (!is_env_var(str, false))
			return (-1);
		*key = ft_strdup(str);
		if (!*key)
			return (malloc_error(0));
		*value = NULL;
		return (1);
	}
	*key = ft_strndup(str, equal - str);
	if (!*key)
		return (malloc_error(0));
	if (!is_env_var(*key, false))
	{
		printf("%s",*key);
		free(*key);
		*key = NULL;
		return (-1);
	}
	return (1);
}

/**
 * Splits a string into key and value at the first '=' character.
 * It will return false if:
 * - {check_env_key} fails.
 * - Memory allocation of value fails.
 * @param str The string to split.
 * @param key Pointer to store the allocated key string.
 * @param value Pointer to store the allocated value string.
 * @param isNull Pointer to store whether the value is NULL (no '=' found).
 * @return - 1 if successful, 0 if memory allocation fails,
 * -1 if the key is invalid.
 * @see check_env_key
 */
int	split_env(const char *str, char **key, char **value, bool *isNull)
{
	const char	*equal = ft_strchr(str, '=');
	int			status;

	status = check_env_key(str, key, value, equal);
	if (status != 1)
		return (status);
	if (equal)
		*value = ft_strdup(equal + 1);
	else
	{
		*value = ft_strdup("");
		*isNull = true;
	}
	if (!*value)
	{
		free(*key);
		*key = NULL;
		*isNull = true;
		return (malloc_error(0));
	}
	return (1);
}

/**
 * Frees the data inside the dynamic array and resets its fields.
 * Does not free the array structure itself.
 * @param arr The array to free
 */
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

/**
 * Initializes a dynamic array with
 * environment variables using [data].
 * @param arr The array to initialize
 * @param data The environment variable strings
 * @return true if successful, false otherwise
 */
bool	init_array(t_array *arr, char **data)
{
	size_t	i;
	t_env	item;

	i = 0;
	arr->used_slots = 0;
	arr->capacity = 2;
	arr->data = ft_calloc(arr->capacity, sizeof(t_env));
	if (!arr->data)
		return (malloc_error(false));
	while (data[i])
	{
		if (!split_env(data[i], &item.key, &item.value, &item.is_nul))
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
