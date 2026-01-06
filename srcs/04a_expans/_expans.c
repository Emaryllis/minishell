/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expans.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:55:31 by julhong           #+#    #+#             */
/*   Updated: 2026/01/06 14:26:40 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// static bool	is_valid_envar(char c)
// {
// 	return (ft_isalpha(c) || (c == '_'));
// }

/**
 * Expands all valid $ENVs in in a string
 * @todo - handle $?
 * @todo - compress
 */
char	*expand_str(char *str, t_msh *ms)
{
	int		i;
	char	*prefix;
	char	*key;
	char	*expans;
	int		j;
	char	*postfix;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			adv_indx_quote(str, &i, '\'');
			i++;
		}
		else if (str[i] == '$'
			&& (ft_isalpha(str[i + 1]) || (str[i + 1] == '_')))
		{
			prefix = ft_substr(str, 0, i++);
			//get expans key
			j = 0;
			while (ft_isalnum(str[i + j]) || str[i + j] == '_')
				j++;
			key = ft_substr(str, i, j);
			expans = get_env(ms->env, key);
			free(key);
			if (expans)
				expans = ft_strdup(expans);
			else
				expans = ft_strdup("");
			//get postfix
			postfix = ft_strdup(&str[i + j]);
			//replace str, and repeat after expans
			free(str);
			str = str3join(prefix, expans, postfix);
			i += ft_strlen(expans);
			free(prefix);
			free(expans);
			free(postfix);
		}
		else
			i++;
	}
	return (str);
}
