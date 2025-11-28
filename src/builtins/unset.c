/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:08:59 by egoh              #+#    #+#             */
/*   Updated: 2025/11/23 13:08:59 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

int	cell_unset(t_ms *ms)
{
	size_t	i;

	if (!ms->args || !ms->args[0] || !ms->args[1])
		return (EXIT_SUCCESS);
	i = 0;
	while (ms->args[++i])
	{
		if (!is_env_var(ms->args[i], false))
			continue ;
		array_remove(ms->env, ms->args[i]);
	}
	return (EXIT_SUCCESS);
}
