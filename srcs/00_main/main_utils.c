/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:52:33 by julhong           #+#    #+#             */
/*   Updated: 2026/01/29 18:18:43 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	msh_consume_sigint(t_msh *ms)
{
	if (g_newsig == SIGINT)
	{
		ms->exstat = 130;
		g_newsig = 0;
		return (1);
	}
	return (0);
}

/**
 * Cleans up all allocated memory in main ms structure.
 * - include cleanup of redirs (inside ast cmds) and any hdoc fds
 */
int	main_cleanup(t_msh *ms)
{
	if (ms->input.line && (free(ms->input.line), true))
		ms->input.line = NULL;
	if (ms->args && (free_2darr((void **)ms->args), true))
		ms->args = NULL;
	if (ms->tk_start && (clear_tokens(&ms->tk_start), true))
		ms->tk_start = NULL;
	if (ms->ast_garbc && (clear_ast_garbage(&ms->ast_garbc), true))
		ms->ast_garbc = NULL;
	if ((ms->shell_exit || ms->input.eof) && ms->env)
	{
		ms->shell_exit = true;
		array_free(ms->env);
		free(ms->env);
	}
	return (1);
}
