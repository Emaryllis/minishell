/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exp_argv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 23:12:02 by julhong           #+#    #+#             */
/*   Updated: 2026/02/11 23:29:22 by julhong          ###   ########.fr       */
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

static void	std_expn_outp(t_expav *v, t_msh *ms)
{
	v->tmp_argv[v->i] = expand_str_envs(v->tmp_argv[v->i], ms, 0);
	if (*v->tmp_argv[v->i] == '\0' && (free(v->tmp_argv[v->i]), 1))
		v->tmp_argv[v->i] = NULL;
	if (!v->tmp_argv[v->i])
		v->i++;
	else
		point_or_process(v);
}

static void	stage_export_tmpav(t_expav *v, char **raw_argv, int *ac, t_msh *ms)
{
	char	**av0_exp;
	int		av0_exp_len;

	av0_exp = expand_argv(raw_argv, 1, ms);
	av0_exp_len = arr_len((void **)av0_exp);
	*ac = *ac - 1 + av0_exp_len;
	*v = (t_expav){.i = -1, .j = 1, .ac_max = *ac * 2};
	v->tmp_argv = malloc((*ac + 1) * sizeof(char *));
	v->tmp_argv[*ac] = NULL;
	while (++v->i < *ac)
	{
		if (v->i < av0_exp_len)
		{
			v->tmp_argv[v->i] = av0_exp[v->i];
			continue ;
		}
		v->tmp_argv[v->i] = ft_strdup(raw_argv[v->i - av0_exp_len + 1]);
	}
	v->output_argv = dup_argv(NULL, v->ac_max);
	v->output_argv[0] = av0_exp[0];
	free(av0_exp);
}

static char	*enforce_assgnm_wrap(char *value, t_expav *v)
{
	if (!(value[0] == '\'' || value[0] == '"'))
	{
		v->tmp_argv[v->i] = str3join("\"", value, "\"");
		free(value);
	}
	else
		v->tmp_argv[v->i] = value;
	return (v->tmp_argv[v->i]);
}

char	**export_expn_argv(char **raw_argv, int ac, t_msh *ms)
{
	t_expav	v;
	t_env	env;
	char	*expnd_val;

	stage_export_tmpav(&v, raw_argv, &ac, ms);
	v.i = 1;
	while (v.i < ac)
	{
		if (split_env(v.tmp_argv[v.i], &env.key, &env.value, &env.is_nul) != 1)
		{
			std_expn_outp(&v, ms);
			continue ;
		}
		env.value = expand_str_envs(env.value, ms, 0);
		free(v.tmp_argv[v.i]);
		v.tmp_argv[v.i] = enforce_assgnm_wrap(env.value, &v);
		strip_split_gmark_loop(&v);
		expnd_val = v.output_argv[v.j - 1];
		v.output_argv[v.j - 1] = str3join(env.key, "=", expnd_val);
		if (free(env.key), free(expnd_val), free(v.tmp_argv[v.i++]), true)
			continue ;
	}
	return (free(v.tmp_argv), v.output_argv[v.j] = NULL, v.output_argv);
}
