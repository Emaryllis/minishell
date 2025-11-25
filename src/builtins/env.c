/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 13:07:26 by egoh              #+#    #+#             */
/*   Updated: 2025/11/23 13:07:26 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static void	print_envs(const t_array *arr)
{
	size_t	i;
	t_env	*item;

	if (!arr || !arr->data)
		return ;
	i = 0;
	while (i < arr->used_slots)
	{
		item = &arr->data[i];
		if (item->key)
		{
			if (item->value)
				printf("%s=%s\n", item->key, item->value);
			else
				printf("%s\n", item->key);
		}
		i++;
	}
}

int	cell_env(t_ms *ms)
{
	print_envs(ms->env);
	return (EXIT_SUCCESS);
}
