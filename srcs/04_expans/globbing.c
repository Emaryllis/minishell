/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:26:12 by julhong           #+#    #+#             */
/*   Updated: 2026/01/14 01:11:50 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

static t_globpat	glob_pattern(char *str)
{
	t_globpat	pat;

	pat.bgn_pat = (*str != JAMES_BOND);
	pat.bgn_dot = (*str == '.');
	pat.end_pat = (str[ft_strlen(str) - 1] != JAMES_BOND);
	pat.chunks = ft_split(str, JAMES_BOND);
	return (pat);
}

bool	glob_match(char *ent, t_globpat pat)
{
	int		i;
	char	*match;

	if (ent[0] == '.' && !pat.bgn_dot)
		return (false);
	i = 0;
	while (pat.chunks[i])
	{
		match = ft_strstr(ent, pat.chunks[i]);
		if (!match)
			return (false);
		if ((i == 0) && pat.bgn_pat && (match != ent))
			return (false);
		ent = match + ft_strlen(pat.chunks[i]);
		if (!pat.chunks[i + 1] && pat.end_pat && *ent != '\0')
			return (false);
		i++;
	}
	return (true);
}

static void	globble_up_loop(t_expav *v)
{
	(void)glob_pattern(*v->tmp_argv);
	(void)glob_match(NULL, (t_globpat){0});
	//run through dir entries
		//check if it is a match
		//accumulate in a tmp_argv

	//if tmp_argv is NULL (no match)
		//then replace JAMES_BOND in original string back to * literal
		//return without freeing
	//else
		//sort tmp_argv
		//add to output_argv (widen space if needed)
		//update pointers
		//free original argv
}

char	**gobble_argv(char **input_argv)
{
	t_expav	v;

	v = (t_expav){.i = -1, .j = 0, .argc = 0};
	while (input_argv[++v.i])
		v.argc++;
	v.ac_max = v.argc * 2;
	v.i = 0;
	v.output_argv = dup_argv(NULL, v.ac_max);
	while (v.i < v.argc)
	{
		if (!ft_strchr(v.tmp_argv[v.i], JAMES_BOND))
		{
			v.output_argv[v.j++] = v.tmp_argv[v.i++];
			continue ;
		}
		(void)globble_up_loop(&v);
		//globble_up_loop() 
			//loops to find next match, expands accordingly
			//no match then replaces JAMES_BOND back to * literal

		//original loop: strip_split_gmark_loop(&v);
		// free(v.tmp_argv[v.i++]);
	}
	return (free(v.tmp_argv), v.output_argv[v.j] = NULL, v.output_argv);
}
