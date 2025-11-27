/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_validators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:00 by egoh              #+#    #+#             */
/*   Updated: 2025/11/27 22:36:00 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

/**
 * Checks if a string is a valid environment variable name.
 * A valid environment variable name starts with a '$'
 * followed by an alphabetic character or underscore, and
 * can contain alphanumeric characters and underscores.
 * Basic Regex: ^\$[A-Za-z_][A-Za-z0-9_]*$
 */
bool	is_env_var(const char *str)
{
	int	i;

	if (!str || str[0] != '$' || !str[1] || (str[1] < 'A' || (str[1] > 'Z'
				&& str[1] < 'a') || str[1] > 'z') && str[1] != '_')
		return (false);
	i = 2;
	while (str[i])
	{
		if ((str[1] < 'A' || (str[1] > 'Z' && str[1] < 'a') || str[1]
				> 'z') && str[1] != '_')
			return (false);
		i++;
	}
	return (true);
}
