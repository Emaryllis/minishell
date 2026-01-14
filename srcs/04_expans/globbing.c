/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:26:12 by julhong           #+#    #+#             */
/*   Updated: 2026/01/15 00:49:58 by julhong          ###   ########.fr       */
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
bool	glob_match(char *d_name, t_globpat pat)
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

/** Extracts, sorts, and adds to output_argv all matching entries
 * - Ext: accumulate pat matches into a tmp (dynamic)
 * - Sort: sort tmp lexicographically
 * - Add: expand output_argv accordingly
 */
static void	globble_up_loop(char *arg, t_expav *m)
{
	t_globpat		pat;
	t_expav			g;
	DIR				*dir;
	struct dirent	*ent;

	pat = extract_glob_pat(arg);
	g = (t_expav){.tmp_argv = dup_argv(NULL, 10), .ac_max = 10};

	//run through dir entries
		//check if it is a match
		//accumulate in a tmp_argv
	dir = opendir(".");
	if (!dir)
		return ; //to treat as no match
	ent = readdir(dir);
	while (ent)
	{
		if (!ft_strcmp(ent->d_name, ".") || !ft_strcmp(ent->d_name, ".."))
			continue ;
		if (glob_match(ent->d_name, pat))
		{
			if (g.i >= g.ac_max)
				g.tmp_argv = realloc_str_arr(g.tmp_argv, g.i, &g.ac_max);
			g.tmp_argv[g.i++] = ft_strdup(ent->d_name);
		}
		ent = readdir(dir);
	}
	closedir(dir);


	//if tmp_argv is NULL (no match)
		//then replace JAMES_BOND in original string back to * literal
		//return without freeing
	//else
		//sort tmp_argv
		//add to output_argv (widen space if needed)
		//update pointers
		//free original argv

	//free2darr chunks in pat
}

char	**gobble_argv(char **input_argv)
{
	t_expav	m;

	m = (t_expav){.output_argv = dup_argv(NULL, 10), .ac_max = 10};
	while (input_argv[m.i])
	{
		if (!ft_strchr(input_argv[m.i], JAMES_BOND))
		{
			m.output_argv[m.j++] = input_argv[m.i++];
			continue ;
		}
		(void)globble_up_loop(input_argv[m.i], &m);
		//globble_up_loop() 
			//loops to find next match, expands accordingly
			//no match then replaces JAMES_BOND back to * literal

		//original loop: strip_split_gmark_loop(&v);
		// free(v.tmp_argv[v.i++]);
	}
	return (free(input_argv), m.output_argv[m.j] = NULL, m.output_argv);
}
