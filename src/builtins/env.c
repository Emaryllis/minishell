/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:07:26 by egoh              #+#    #+#             */
/*   Updated: 2025/11/29 02:21:22 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

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
