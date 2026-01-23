/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp1_str_envs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:55:31 by julhong           #+#    #+#             */
/*   Updated: 2026/01/23 01:37:10 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	hdl_evnlvl_quotes(char *str, t_expstr *v)
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

/**
 * Expands $ENV at current index of str
 * - Replaces creates new str to replace (and free) old one
 * - Updates pointer to unprocessed portion post expansion
 */
static char	*exp_and_replace(char *str, t_expstr *v, t_msh *ms)
{
	v->dollar_ind = v->i;
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
	v->i = v->dollar_ind + ft_strlen(v->expans);
	return (free(v->prefix), free(v->expans), free(v->postfx), str);
}

/**
 * Expands all valid $ENVs in in a string
 * - quotes remain
 * - Default mode is_hdoc == 0: Normal quote-specific aware expans
 * - Heredoc mode is_hdoc == 1 mode: Quote agnostic expans
 */
char	*expand_str_envs(char *str, t_msh *ms, int is_hdoc)
{
	t_expstr	v;

	if (!ft_strchr(str, '$'))
		return (str);
	v.in_dquote = false;
	v.i = 0;
	while (str[v.i])
	{
		if (!is_hdoc
			&& (str[v.i] == '"' || (str[v.i] == '\'' && !v.in_dquote)))
			hdl_evnlvl_quotes(str, &v);
		else if (str[v.i] == '$' && (str[v.i + 1] == '?'
				|| (ft_isalpha(str[v.i + 1]) || (str[v.i + 1] == '_'))))
			str = exp_and_replace(str, &v, ms);
		else
			v.i++;
	}
	return (str);
}
