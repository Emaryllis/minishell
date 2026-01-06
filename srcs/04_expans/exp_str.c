/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:55:31 by julhong           #+#    #+#             */
/*   Updated: 2026/01/07 00:14:47 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"


static void	hdl_expn_quotes(char *str, t_expstr *v)
{
	if (str[v->i] == '"')
	{
		if (!v->in_dquote)
			v->in_dquote = true;
		else
			v->in_dquote = false;
		v->i++;
	}
	else if (str[v->i] == '\'' && !v->in_dquote)
	{
		adv_indx_quote(str, &v->i, '\'');
		v->i++;
	}
}

static char	*exp_and_replace(char *str, t_expstr *v, t_msh *ms)
{
	v->prefix = ft_substr(str, 0, v->i++);
	if (str[v->i] == '?')
	{
		v->j = 1;
		v->expans = ft_itoa(ms->exit_status);
	}
	else
	{
		v->j = 0;
		while (ft_isalnum(str[v->i + v->j]) || str[v->i + v->j] == '_')
			v->j++;
		v->key = ft_substr(str, v->i, v->j);
		v->expans = get_env(ms->env, v->key);
		free(v->key);
		if (v->expans)
			v->expans = ft_strdup(v->expans);
		else
			v->expans = ft_strdup("");
	}
	v->postfx = ft_strdup(&str[v->i + v->j]);
	free(str);
	str = str3join(v->prefix, v->expans, v->postfx);
	v->i += ft_strlen(v->expans);
	return (free(v->prefix), free(v->expans), free(v->postfx), str);
}

/**
 * Expands all valid $ENVs in in a string.
 * - Skips single quote sections (not inside d_quotes)
 * - Traverses up to $ENV for prefix substr (? or valid key)
 * - Traverses $ENV for expans substr
 * - Rest of the string after $ENV is postfx strdup
 */
char	*expand_str(char *str, t_msh *ms)
{
	t_expstr	v;

	if (!ft_strchr(str, '$'))
		return (str);
	v.in_dquote = false;
	v.i = 0;
	while (str[v.i])
	{
		if (str[v.i] == '"' || (str[v.i] == '\'' && !v.in_dquote))
			hdl_expn_quotes(str, &v);
		else if (str[v.i] == '$' && (str[v.i + 1] == '?'
				|| (ft_isalpha(str[v.i + 1]) || (str[v.i + 1] == '_'))))
			str = exp_and_replace(str, &v, ms);
		else
			v.i++;
	}
	return (str);
}
