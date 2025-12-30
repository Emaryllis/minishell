/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:07:46 by egoh              #+#    #+#             */
/*   Updated: 2025/12/30 14:24:32 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	parse_args(t_msh *ms, t_env *item, size_t i, int *ret)
{
	const int	code_s = split_env(ms->args[i], &item->key, &item->value);
	bool		code;

	if (code_s == 0)
		*ret = -1;
	else if (code_s == -1)
		*ret = (eprintf(NAME": export: `%s': not a valid identifier\n",
					ms->args[i]), 1);
	if (code_s != 1)
		return ;
	code = set_env(ms->env, item->key, item->value);
	if (code)
	{
		free(item->key);
		free(item->value);
		return ;
	}
	if (get_env(ms->env, item->key) == NULL)
	{
		if (!array_push(ms->env, *item, true))
			free(item->key);
		else
			return ;
	}
	*ret = -1;
}

static void	print_export(const t_array *arr)
{
	t_env	*sorted;
	size_t	i;

	sorted = quicksort_env(arr);
	if (!sorted)
		return ;
	i = 0;
	while (i < arr->used_slots)
	{
		if (sorted[i].key && sorted[i].value)
			printf("declare -x %s=\"%s\"\n", sorted[i].key, sorted[i].value);
		else if (sorted[i].key)
			printf("declare -x %s\n", sorted[i].key);
		i++;
	}
	free(sorted);
}

/**
 * @return 1 if memory allocation fails or invalid identifier,
 * 0 otherwise
 */
int	cell_export(t_msh *ms)
{
	size_t	i;
	t_env	item;
	int		code;

	if (!ms->env || !ms->args)
		return (EXIT_SUCCESS);
	if (ms->args[0] && !ms->args[1])
	{
		print_export(ms->env);
		return (EXIT_SUCCESS);
	}
	i = 0;
	code = EXIT_SUCCESS;
	while (ms->args[++i])
	{
		parse_args(ms, &item, i, &code);
		if (code == -1)
			return (malloc_error(EXIT_FAILURE));
	}
	return (code);
}
