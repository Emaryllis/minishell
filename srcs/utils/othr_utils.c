/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:30:00 by egoh              #+#    #+#             */
/*   Updated: 2026/02/04 19:52:56 by egoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

int	malloc_error(int ret)
{
	ft_printfd(2, NAME": malloc: Cannot allocate memory\n");
	return (ret);
}

int	malloc_fail_exit(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}

int	parseCFlag(char *line, t_msh *ms)
{

	if (lex_tokens(ms, line))
	{
		ms->ast_root = build_ast(ms);
		if (!ms->ast_root && main_cleanup(ms))
			return (ms->exstat);
		debug_print_ast(ms->ast_root, 0);
		execute_ast(ms);
		main_cleanup(ms);
	}
	return (ms->exstat);
}