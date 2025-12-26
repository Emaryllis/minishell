/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:55:12 by egoh              #+#    #+#             */
/*   Updated: 2025/12/17 12:03:30 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minsh.h"

static t_env	*copy_env_array(const t_array *arr)
{
	t_env	*copy;
	size_t	i;

	if (!arr || arr->used_slots == 0)
		return (NULL);
	copy = ft_calloc(arr->used_slots, sizeof(t_env));
	if (!copy)
	{
		malloc_error(0);
		return (NULL);
	}
	i = 0;
	while (i < arr->used_slots)
	{
		copy[i] = arr->data[i];
		i++;
	}
	return (copy);
}

static size_t	partition(t_env *arr, size_t low, size_t high)
{
	const t_env	pivot = arr[high];
	size_t		i;
	size_t		j;
	t_env		tmp;

	i = low;
	j = low;
	while (j < high)
	{
		if (arr[j].key && (!pivot.key || strcmp(arr[j].key, pivot.key) <= 0))
		{
			tmp = arr[i];
			arr[i++] = arr[j];
			arr[j] = tmp;
		}
		j++;
	}
	if (pivot.key)
	{
		tmp = arr[i];
		arr[i] = arr[high];
		arr[high] = tmp;
	}
	return (i);
}

static void	quicksort_env_internal(t_env *arr, size_t low, size_t high)
{
	size_t	pi;

	while (low < high)
	{
		pi = partition(arr, low, high);
		if (pi - low < high - pi)
		{
			if (pi > 0)
				quicksort_env_internal(arr, low, pi - 1);
			low = pi + 1;
		}
		else
		{
			quicksort_env_internal(arr, pi + 1, high);
			if (pi > 0)
				high = pi - 1;
		}
	}
}

t_env	*quicksort_env(const t_array *arr)
{
	t_env	*copy;

	if (!arr || arr->used_slots == 0)
		return (NULL);
	copy = copy_env_array(arr);
	if (!copy)
		return (NULL);
	quicksort_env_internal(copy, 0, arr->used_slots - 1);
	return (copy);
}
