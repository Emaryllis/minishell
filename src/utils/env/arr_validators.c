/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_validators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 22:36:00 by egoh              #+#    #+#             */
/*   Updated: 2025/12/04 15:23:44 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
 * Checks if a string is a valid environment variable name.
 * A valid environment variable name starts with a '$'
 * followed by an alphabetic character or underscore, and
 * can contain alphanumeric characters and underscores.
 * Basic Regex: ^[A-Za-z_][A-Za-z0-9_]*$
 * With dollar sign: ^\$[A-Za-z_][A-Za-z0-9_]*$
 * @param str The string to check.
 * @param dollar_sign If true, expects the string to start with '$'.
 * @return true if the string is valid, false otherwise.
 */
bool	is_env_var(const char *str, bool dollar_sign)
{
	int	i;

	if (dollar_sign)
	{
		if (!str || (str[0] != '$'))
			return (false);
		return (is_env_var(str + 1, false));
	}
	if (!str || (str[0] < 'A' || (str[0] > 'Z'
				&& str[0] < 'a') || str[0] > 'z') && str[0] != '_')
		return (false);
	i = 1;
	while (str[i])
	{
		if ((str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i]
				> 'z') && (str[i] < '0' || str[i] > '9') && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
