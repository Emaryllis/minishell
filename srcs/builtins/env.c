/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:07:26 by egoh              #+#    #+#             */
/*   Updated: 2026/02/05 16:47:02 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	cell_env(t_msh *ms)
{
	size_t	i;
	t_array	*arr;

	if (ms->args[1])
	{
		ft_printfd(2, "env: too many arguments\n");
		return (EXIT_FAILURE);
	}
	if (!ms->env || !ms->env->data)
		return (EXIT_SUCCESS);
	i = 0;
	arr = ms->env;
	while (i < arr->used_slots)
	{
		if (arr->data[i].key && arr->data[i].value && !arr->data[i].is_nul)
			printf("%s=%s\n", arr->data[i].key, arr->data[i].value);
		i++;
	}
	return (EXIT_SUCCESS);
}
