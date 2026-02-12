/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp2_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:51:41 by julhong           #+#    #+#             */
/*   Updated: 2026/02/11 23:29:44 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static void	point_or_process(t_expav *v)
{
	if (!ft_strchr(v->tmp_argv[v->i], ' ')
		&& !ft_strchr(v->tmp_argv[v->i], '"')
		&& !ft_strchr(v->tmp_argv[v->i], '\'')
		&& !ft_strchr(v->tmp_argv[v->i], '*'))
		v->output_argv[v->j++] = v->tmp_argv[v->i++];
	else
	{
		strip_split_gmark_loop(v);
		free(v->tmp_argv[v->i++]);
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
	{
		v.tmp_argv[v.i] = expand_str_envs(v.tmp_argv[v.i], ms, 0);
		if (*v.tmp_argv[v.i] == '\0' && (free(v.tmp_argv[v.i]), 1))
			v.tmp_argv[v.i] = NULL;
	}
	v.i = 0;
	v.output_argv = dup_argv(NULL, v.ac_max);
	while (v.i < ac)
	{
		if (!v.tmp_argv[v.i])
		{
			v.i++;
			continue ;
		}
		point_or_process(&v);
	}
	free(v.tmp_argv);
	v.output_argv[v.j] = NULL;
	return (v.output_argv = globble_argv(v.output_argv));
}
