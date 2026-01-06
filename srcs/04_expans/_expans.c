/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expans.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:51:41 by julhong           #+#    #+#             */
/*   Updated: 2026/01/07 01:27:13 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	hndl_quote(char **cur, char *arg, int *i, t_quote *q)
{
	char	*start;

	start = *cur;
	if ((*start == '\'' && *q == D_QUOTE) || (*start == '"' && *q == S_QUOTE))
		arg[(*i)++] = *start;
	else if ((*start == '\'' && *q == S_QUOTE)
		|| (*start == '"' && *q == D_QUOTE))
		*q = NO_QUOTE;
	else if (*start == '\'' && *q == NO_QUOTE)
		*q = S_QUOTE;
	else if (*start == '"' && *q == NO_QUOTE)
		*q = D_QUOTE;
	*cur = ++start;
}

/**
 * Returns the arg (the next word) and str (ptr to extent of strip &/or split)
 * 
 * Return Usage:
 * - If *str == '\0' indicates finished stripping &/or splitting an arg
 */
t_stripsplt	strip_and_split(char *str)
{
	char	*arg;
	t_quote	quote;
	int		i;

	arg = ft_strdup(str);
	quote = NO_QUOTE;
	i = 0;
	while(*str)
	{
		if (ft_strchr("'\"", *str))
			hndl_quote(&str, arg, &i, &quote);
		else if (*str == ' ' && quote == NO_QUOTE)
		{
			arg[i] = '\0';
			while (*str == ' ')
				str++;
			break ;
		}
		else
			arg[i++] = *str++;
	}
	arg[i] = '\0';
	return ((t_stripsplt){arg, str});
}

static char	**realloc_final_av(char **final_argv, int ac_cur, int *ac_max)
{
	char	**tmp;
	int		i;

	*ac_max *= 2;
	tmp = dup_argv(NULL, *ac_max);
	i = -1;
	while (++i < ac_cur)
		tmp[i] = final_argv[i];
	free(final_argv);
	final_argv = tmp;
	return (final_argv);
}

static void	strip_and_split_loop(t_expav *v)
{
	t_stripsplt	ss_res;
	
	ss_res = strip_and_split(v->exp_argv[v->i]);
	v->final_argv[v->j++] = ss_res.sub_arg;
	while (*ss_res.split_prog != '\0')
	{
		ss_res = strip_and_split(ss_res.split_prog);
		if (v->j + 1 >= v->ac_max)
			v->final_argv = realloc_final_av(v->final_argv, v->j, &v->ac_max);
		v->final_argv[v->j++] = ss_res.sub_arg;
	}
}

/**
 * Gets the final execve ready argv
 * - Dups raw parser cmd-node argv (unexpanded, with quotes)
 * - Runs expand_str on each entry (quotes remain)
 * - Strips (of quotes) and splits (on unquoted whitespace) argv entries
 * - Adjusts argv, argc
 */
char	**expand_argv(char **av, int ac, t_msh *ms)
{
	t_expav	v;
	
	v.exp_argv = dup_argv(av, ac);
	v.i = -1;
	while (v.exp_argv[++v.i])
		v.exp_argv[v.i] = expand_str(v.exp_argv[v.i], ms);
	v.ac_max = ac * 2;
	v.final_argv = dup_argv(NULL, v.ac_max);
	v.i = 0;
	v.j = 0;
	while (v.i < ac)
	{
		if (!ft_strchr(v.exp_argv[v.i], ' ') && !ft_strchr(v.exp_argv[v.i], '"')
			&& !ft_strchr(v.exp_argv[v.i], '\''))
		{
			v.final_argv[v.j++] = v.exp_argv[v.i++];
			continue ;
		}
		strip_and_split_loop(&v);
		free(v.exp_argv[v.i++]);
	}
	v.final_argv[v.j] = NULL;
	return (free(v.exp_argv), v.final_argv);
}
