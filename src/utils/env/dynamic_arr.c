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

/**
 * Checks and extracts the key from the environment string.
 * If there is no '=' character, it treats the entire string as the key.
 * It will return false & free key if:
 * - The key is not a valid environment variable name. (see is_env_var)
 * - Memory allocation fails.
 * @param str The string to check.
 * @param key Pointer to store the allocated key string.
 * @param value Pointer to store the allocated value string.
 * @param equal Pointer to the '=' character in the string, or NULL if not found.
 * @return true if successful, false otherwise.
 * @see is_env_var
 */
static bool	check_env_key(const char *str, char **key, char **value,
							const char *equal)
{
	if (!equal)
	{
		if (!is_env_var(str, false))
			return (false);
		*key = ft_strdup(str);
		if (!*key)
			return (false);
		*value = NULL;
		return (true);
	}
	*key = ft_strndup(str, equal - str);
	if (!*key)
		return (false);
	if (!is_env_var(*key, false))
	{
		printf("%s",*key);
		free(*key);
		*key = NULL;
		return (false);
	}
	return (true);
}

/**
 * Splits a string into key and value at the first '=' character.
 * It will return false if:
 * - {check_env_key} fails.
 * - Memory allocation of value fails.
 * @param str The string to split.
 * @param key Pointer to store the allocated key string.
 * @param value Pointer to store the allocated value string.
 * @return true if successful, false otherwise.
 */
bool	split_env(const char *str, char **key, char **value)
{
	const char	*equal = ft_strchr(str, '=');

	if (!check_env_key(str, key, value, equal))
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
 * Initalizes a dynamic array with
 * environment variables using {data}.
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
