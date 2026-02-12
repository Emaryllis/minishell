/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:07:26 by egoh              #+#    #+#             */
/*   Updated: 2026/02/13 01:00:36 by julhong          ###   ########.fr       */
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
		{
			if (ft_printf("%s=%s\n"
					, arr->data[i].key, arr->data[i].value) == -1)
				return (perror(NAME": write error"), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
