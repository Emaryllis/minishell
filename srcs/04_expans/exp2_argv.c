/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp2_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:51:41 by julhong           #+#    #+#             */
/*   Updated: 2026/01/08 23:56:57 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	hndl_ssglvl_quotes(char **cur, char *arg, int *i, t_quote *q)
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
t_strips	strip_split_gmark_nxt(char *str)
{
	char	*arg;
	t_quote	quote;
	int		i;

	arg = ft_strdup(str);
	quote = NO_QUOTE;
	i = 0;
	while (*str)
	{
		if (ft_strchr("'\"", *str))
			hndl_ssglvl_quotes(&str, arg, &i, &quote);
		else if (*str == ' ' && quote == NO_QUOTE)
		{
			arg[i] = '\0';
			while (*str == ' ')
				str++;
			break ;
		}
		else if ((*str == '*' && quote == NO_QUOTE) && str++)
			arg[i++] = JAMES_BOND;
		else
			arg[i++] = *str++;
	}
	return (arg[i] = '\0', (t_strips){arg, str});
}

/**
 * Increaes capacity of a fixed char *array[]
 * - repoints to origianl strings
 * - does not NULL terminate
 * 
 * Usage:
 * - use in a condition and/or loop to ensure size_used can fit in size_cap
 */
char	**realloc_str_arr(char **input_arr, int size_used, int *size_cap)
{
	char	**tmp;
	int		i;

	*size_cap *= 2;
	tmp = dup_argv(NULL, *size_cap);
	i = -1;
	while (++i < size_used)
		tmp[i] = input_arr[i];
	free(input_arr);
	input_arr = tmp;
	return (input_arr);
}

static void	strip_split_gmark_loop(t_expav *v)
{
	t_strips	ssg_ret;

	ssg_ret = strip_split_gmark_nxt(v->tmp_argv[v->i]);
	v->output_argv[v->j++] = ssg_ret.sub_arg;
	while (*ssg_ret.split_prog != '\0')
	{
		ssg_ret = strip_split_gmark_nxt(ssg_ret.split_prog);
		if (v->j + 1 >= v->ac_max)
			v->output_argv = realloc_str_arr(v->output_argv, v->j, &v->ac_max);
		v->output_argv[v->j++] = ssg_ret.sub_arg;
	}
}

/**
 * Expansion of char **argv w/o globbing-up (but globs are marked)
 * - Dups raw parser cmd-node argv (unexpanded, with quotes)
 * - Runs expand_str_envs on each entry (quotes remain)
 * - Strips (of quotes) and splits (on unquoted whitespace) argv entries
 */
char	**expand_argv(char **raw_argv, int ac, t_msh *ms)
{
	t_expav	v;

	v.tmp_argv = dup_argv(raw_argv, ac);
	v.i = -1;
	while (v.tmp_argv[++v.i])
		v.tmp_argv[v.i] = expand_str_envs(v.tmp_argv[v.i], ms);
	v = (t_expav){.i = 0, .j = 0, .ac_max = ac * 2};
	v.output_argv = dup_argv(NULL, v.ac_max);
	while (v.i < ac)
	{
		if (!ft_strchr(v.tmp_argv[v.i], ' ') && !ft_strchr(v.tmp_argv[v.i], '"')
			&& !ft_strchr(v.tmp_argv[v.i], '\''))
		{
			v.output_argv[v.j++] = v.tmp_argv[v.i++];
			continue ;
		}
		strip_split_gmark_loop(&v);
		free(v.tmp_argv[v.i++]);
	}
	return (free(v.tmp_argv), v.output_argv[v.j] = NULL, v.output_argv);
}
