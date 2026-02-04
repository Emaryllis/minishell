/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:07:46 by egoh              #+#    #+#             */
/*   Updated: 2026/01/04 17:30:29 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	parse_args(t_msh *ms, t_env *i, size_t j, int *ret)
{
	const int	s_cde = split_env(ms->args[j], &i->key, &i->value, &i->is_nul);
	bool		code;

	if (s_cde == 0)
		*ret = -1;
	else if (s_cde == -1)
		*ret = (ft_printfd(2, NAME": export: `%s': not a valid identifier\n",
					ms->args[j]), 1);
	if (s_cde != 1)
		return ;
	code = set_env(ms->env, i->key, i->value);
	if (code)
	{
		free(i->key);
		free(i->value);
		return ;
	}
	if (get_env(ms->env, i->key) == NULL)
	{
		if (!array_push(ms->env, *i, true))
			free(i->key);
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
		if (sorted[i].key && sorted[i].value && !sorted[i].is_nul)
			printf("declare -x %s=\"%s\"\n", sorted[i].key, sorted[i].value);
		else if (sorted[i].key || (sorted[i].value && sorted[i].is_nul))
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
