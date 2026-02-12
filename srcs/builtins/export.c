/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:07:46 by egoh              #+#    #+#             */
/*   Updated: 2026/02/13 01:12:04 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	parse_args(t_msh *ms, t_env *i, size_t j, int *ret)
{
	const int	s_cde = split_env(ms->args[j], &i->key, &i->value, &i->is_nul);

	if (s_cde == 0)
		*ret = -1;
	else if (s_cde == -1)
		*ret = (ft_printfd(2, NAME": export: `%s': not a valid identifier\n",
					ms->args[j]), 1);
	if (s_cde != 1)
		return ;
	if (!ft_strchr(ms->args[j], '='))
	{
		if (get_env(ms->env, i->key) == NULL && array_push(ms->env, *i, true))
			return ;
		free(i->key);
		free(i->value);
		return ;
	}
	if (set_env(ms->env, i->key, i->value) == 1
		&& (free(i->key), free(i->value), 1))
		return ;
	if (get_env(ms->env, i->key) == NULL && array_push(ms->env, *i, true))
		return ;
	free(i->key);
	free(i->value);
}

static int	print_export(const t_array *arr)
{
	t_env	*sorted;
	size_t	i;

	sorted = quicksort_env(arr);
	if (!sorted)
		return (EXIT_FAILURE);
	i = 0;
	while (i < arr->used_slots)
	{
		if (sorted[i].key && sorted[i].value && !sorted[i].is_nul)
		{
			if (ft_printf("declare -x %s=\"%s\"\n"
					, sorted[i].key, sorted[i].value) == -1)
				return (perror(NAME": write error"), EXIT_FAILURE);
		}
		else if (sorted[i].key && sorted[i].is_nul)
		{
			if (ft_printf("declare -x %s\n", sorted[i].key) == -1)
				return (perror(NAME": write error"), EXIT_FAILURE);
		}
		i++;
	}
	free(sorted);
	return (EXIT_SUCCESS);
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
		return (print_export(ms->env));
	i = 0;
	code = EXIT_SUCCESS;
	while (ms->args[++i])
	{
		parse_args(ms, &item, i, &code);
		if (code == -1)
			return (EXIT_FAILURE);
	}
	return (code);
}
