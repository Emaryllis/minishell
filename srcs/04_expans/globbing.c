/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:26:12 by julhong           #+#    #+#             */
/*   Updated: 2026/01/17 01:41:54 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

/** Gets the glob pattern of a string
 * 
 * Notes: 
 * - assumes str has a glob (checks alrdy done)
 * - reverts glob marker back to literal * aft extraction (use if 0 matches)
 * 
 * Returns:
 * - a t_globpat struct with glob pattern data
 * - if pat.chunks[i] == NULL then there are no pat chunks i.e. entirely '*'
 */
static t_globpat	extract_glob_pat(char *str)
{
	t_globpat	pat;
	char		*revert;

	pat.bgn_pat = (*str != JAMES_BOND);
	pat.bgn_dot = (*str == '.');
	pat.end_pat = (str[ft_strlen(str) - 1] != JAMES_BOND);
	pat.chunks = ft_split(str, JAMES_BOND);
	revert = ft_strchr(str, JAMES_BOND);
	while (revert)
	{
		*revert = '*';
		revert++;
		revert = ft_strchr(revert, JAMES_BOND);
	}
	return (pat);
}

/** Tests whether an entry matches the glob pattern in pat
 * 
 * Notes:
 * - if the ent starts with '.' (hidden file) then "dot rule" applies
 * - Dot Rule: pat has to start with a literal, and that lit is also a '.'
 */
static bool	glob_match(char *d_name, t_globpat pat)
{
	int		i;
	char	*match;

	if (d_name[0] == '.' && !pat.bgn_dot)
		return (false);
	i = 0;
	while (pat.chunks[i])
	{
		match = ft_strstr(d_name, pat.chunks[i]);
		if (!match)
			return (false);
		if ((i == 0) && pat.bgn_pat && (match != d_name))
			return (false);
		d_name = match + ft_strlen(pat.chunks[i]);
		if (!pat.chunks[i + 1] && pat.end_pat && *d_name != '\0')
			return (false);
		i++;
	}
	return (true);
}

/** Ret a sorted str arr of args from glob matches
 * - takes original arg, extracts pat, and reverts glob marker to literal
 * - checks dir for matches against pattern (dot and hidden rules asserted)
 * - dynamically accumulate into str arr, sorts and returns to caller
 * - Returns NULL if 0 matches (same as opendir failure)
 */
static char	**glob_output(char *arg)
{
	t_globout	v;

	v = (t_globout){.slot = 0, .ac_max = 10};
	v.dir = opendir(".");
	if (!v.dir)
		return (NULL);
	v.pat = extract_glob_pat(arg);
	v.glob_arr = dup_argv(NULL, v.ac_max);
	v.ent = readdir(v.dir);
	while (v.ent)
	{
		if (glob_match(v.ent->d_name, v.pat))
		{
			if (v.slot >= v.ac_max)
				v.glob_arr = realloc_str_arr(v.glob_arr, v.slot,
						&v.ac_max, v.ac_max * 2);
			v.glob_arr[v.slot++] = ft_strdup(v.ent->d_name);
		}
		v.ent = readdir(v.dir);
	}
	if (closedir(v.dir), free_2darr((void **)v.pat.chunks), v.slot == 0)
		return (free(v.glob_arr), NULL);
	return (v.glob_arr[v.slot] = NULL, msh_lex_sort(v.glob_arr), v.glob_arr);
}

/** Finalizes the result of globbing into output_argv
 * - reallocs if necessary (>1 glob match)
 * - points output_argv to strings (ownership transf)
 * - frees the consumed glob_arr 
 */
static void	glob_exp(t_expav *m, char **glob_arr)
{
	int	glob_len;
	int	glob_idx;

	glob_len = arr_len((void **)glob_arr);
	if (glob_len == 1)
		m->output_argv[m->j++] = *glob_arr;
	else
	{
		m->output_argv = realloc_str_arr(m->output_argv, m->j, &m->ac_max,
				m->ac_max + glob_len - 1);
		glob_idx = 0;
		while (glob_arr[glob_idx])
			m->output_argv[m->j++] = glob_arr[glob_idx++];
	}
	free(glob_arr);
}

char	**globble_argv(char **input_argv)
{
	t_expav	m;
	char	**glob_arr;

	m = (t_expav){0};
	m.ac_max = arr_len((void **)input_argv);
	m.output_argv = dup_argv(NULL, m.ac_max);
	while (input_argv[m.i])
	{
		if (!ft_strchr(input_argv[m.i], JAMES_BOND))
		{
			m.output_argv[m.j++] = input_argv[m.i++];
			continue ;
		}
		glob_arr = glob_output(input_argv[m.i]);
		if (!glob_arr)
		{
			m.output_argv[m.j++] = input_argv[m.i++];
			continue ;
		}
		glob_exp(&m, glob_arr);
		free(input_argv[m.i++]);
	}
	return (free(input_argv), m.output_argv[m.j] = NULL, m.output_argv);
}
