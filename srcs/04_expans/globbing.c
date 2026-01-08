/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:26:12 by julhong           #+#    #+#             */
/*   Updated: 2026/01/09 00:10:57 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

char	**gobble_argv(char **interim_argv)
{
	t_expav	v;

	v = (t_expav){.i = -1, .ac_cur = 0};
	while (interim_argv[++v.i])
		v.ac_cur++;
	v = (t_expav){.i = 0, .j = 0, .ac_max = v.ac_cur * 2};
	v.output_argv = dup_argv(NULL, v.ac_max);
	while (v.i < v.ac_cur)
	{
		if (!ft_strchr(v.tmp_argv[v.i], JAMES_BOND))
		{
			v.output_argv[v.j++] = v.tmp_argv[v.i++];
			continue ;
		}
		//globble_up_loop() 
			//loops to find next match, expands accordingly
			//no match then replaces JAMES_BOND back to * literal

		//original loop: strip_split_gmark_loop(&v);
		free(v.tmp_argv[v.i++]);
	}
	return (free(v.tmp_argv), v.output_argv[v.j] = NULL, v.output_argv);
}
