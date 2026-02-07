/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp2_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:51:41 by julhong           #+#    #+#             */
/*   Updated: 2026/02/08 02:52:23 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

void	quote_filter(char **cur, char *arg, int *i, t_quote *q)
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

/** Quote aware stripping, splitting, glob marking of a string
 * Returns: 
 * - the (new) sub-arg
 * - str (ptr to remainder of str to process)
 * 
 * Usage:
 * - *str != '\0' indicates more to process
 * - *str == '\0' indicates finished stripping &/or splitting the arg
 */
static t_strips	strip_split_gmark_nxt(char *str)
{
	char	*arg;
	t_quote	quote;
	int		i;

	adv_ptr_isspace(&str);
	arg = ft_strdup(str);
	quote = NO_QUOTE;
	i = 0;
	while (*str)
	{
		if (ft_strchr("'\"", *str))
			quote_filter(&str, arg, &i, &quote);
		else if (ft_isspace(*str) && quote == NO_QUOTE)
		{
			adv_ptr_isspace(&str);
			arg[i] = '\0';
			break ;
		}
		else if ((*str == '*' && quote == NO_QUOTE) && str++)
			arg[i++] = JAMES_BOND;
		else
			arg[i++] = *str++;
	}
	return (arg[i] = '\0', (t_strips){arg, str});
}

static void	strip_split_gmark_loop(t_expav *v)
{
	t_strips	ssg_ret;

	ssg_ret = strip_split_gmark_nxt(v->tmp_argv[v->i]);
	v->output_argv[v->j++] = ssg_ret.sub_arg;
	while (*ssg_ret.split_prog != '\0')
	{
		ssg_ret = strip_split_gmark_nxt(ssg_ret.split_prog);
		if (v->j >= v->ac_max)
			v->output_argv = realloc_str_arr(v->output_argv, v->j, &v->ac_max,
					v->ac_max * 2);
		v->output_argv[v->j++] = ssg_ret.sub_arg;
	}
}

/**
 * Expansion of char **argv
 * - Dups raw parser cmd-node argv (unexpanded, with quotes)
 * - Runs expand_str_envs on each entry (quotes remain)
 * - Strips (of quotes) and splits (on unquoted whitespace) argv entries
 */
char	**expand_argv(char **raw_argv, int ac, t_msh *ms)
{
	t_expav	v;

	v = (t_expav){.i = -1, .j = 0, .ac_max = ac * 2};
	v.tmp_argv = dup_argv(raw_argv, ac);
	while (v.tmp_argv[++v.i])
		v.tmp_argv[v.i] = expand_str_envs(v.tmp_argv[v.i], ms, 0);
	v.i = 0;
	v.output_argv = dup_argv(NULL, v.ac_max);
	while (v.i < ac)
	{
		if (!ft_strchr(v.tmp_argv[v.i], ' ')
			&& !ft_strchr(v.tmp_argv[v.i], '"')
			&& !ft_strchr(v.tmp_argv[v.i], '\'')
			&& !ft_strchr(v.tmp_argv[v.i], '*'))
		{
			v.output_argv[v.j++] = v.tmp_argv[v.i++];
			continue ;
		}
		strip_split_gmark_loop(&v);
		free(v.tmp_argv[v.i++]);
	}
	free(v.tmp_argv);
	v.output_argv[v.j] = NULL;
	return (v.output_argv = globble_argv(v.output_argv));
}

char	**export_expn_argv(char **raw_argv, int ac, t_msh *ms)
{
	t_expav	v;
	char	**av0_exp;
	int		av0_exp_len;
	char	*key;
	char	*eql;
	char	*val;
	char	*tmp;

	av0_exp = expand_argv(raw_argv, 1, ms);
	av0_exp_len = arr_len((void **)av0_exp);
	ac = ac - 1 + av0_exp_len;
	v = (t_expav){.i = -1, .j = 1, .ac_max = ac * 2};
	v.tmp_argv = malloc((ac + 1) * sizeof(char *));
	v.tmp_argv[ac] = NULL;
	while (++v.i < ac)
	{
		if (v.i < av0_exp_len)
		{
			v.tmp_argv[v.i] = av0_exp[v.i];
			continue ;
		}
		v.tmp_argv[v.i] = ft_strdup(raw_argv[v.i - av0_exp_len + 1]);
	}
	v.output_argv = dup_argv(NULL, v.ac_max);
	v.output_argv[0] = av0_exp[0];
	free(av0_exp);
	v.i = 1;
	while (v.i < ac)
	{
		eql = ft_strchr(v.tmp_argv[v.i], '=');
		if (eql)
			key = ft_substr(v.tmp_argv[v.i], 0, eql - v.tmp_argv[v.i]);
		if (!eql || (!is_env_var(key, false) && (free(key), true)))
		{
			v.tmp_argv[v.i] = expand_str_envs(v.tmp_argv[v.i], ms, 0);
			if (!ft_strchr(v.tmp_argv[v.i], ' ')
				&& !ft_strchr(v.tmp_argv[v.i], '"')
				&& !ft_strchr(v.tmp_argv[v.i], '\'')
				&& !ft_strchr(v.tmp_argv[v.i], '*'))
			{
				v.output_argv[v.j++] = v.tmp_argv[v.i++];
				continue ;
			}
			strip_split_gmark_loop(&v);
			free(v.tmp_argv[v.i++]);
			continue ;
		}
		val = ft_strdup(eql + 1);
		val = expand_str_envs(val, ms, 0);
		tmp = NULL;
		if (!(val[0] == '\'' || val[0] == '"'))
		{
			tmp = str3join("\"", val, "\"");
			free(val);
			val = tmp;
		}
		free(v.tmp_argv[v.i]);
		v.tmp_argv[v.i] = val;
		strip_split_gmark_loop(&v);
		tmp = v.output_argv[v.j - 1];
		v.output_argv[v.j - 1] = str3join(key, "=", tmp);
		if (free(key), free(tmp), true)
			free(v.tmp_argv[v.i++]);
	}
	return (free(v.tmp_argv), v.output_argv[v.j] = NULL, v.output_argv);
}
