/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:07:26 by egoh              #+#    #+#             */
/*   Updated: 2025/12/04 16:18:42 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	cell_env(t_ms *ms)
{
	size_t	i;

	if (!ms->env || !ms->env->data)
		return (EXIT_SUCCESS);
	i = 0;
	while (i < ms->env->used_slots)
	{
		if (ms->env->data[i].key && ms->env->data[i].value)
			printf("%s=%s\n", ms->env->data[i].key, ms->env->data[i].value);
		i++;
	}
	return (EXIT_SUCCESS);
}
