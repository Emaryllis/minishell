/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julhong <julhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:23:57 by julhong           #+#    #+#             */
/*   Updated: 2026/02/01 22:34:51 by julhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minsh.h"

// Collects t_redir nodes of type hdoc in linked list
void	collect_hdoc(t_redir **hdoc_start, t_redir *new_hdoc)
{
	t_redir	*last;

	if (!hdoc_start || !new_hdoc)
		return ;
	if (*hdoc_start == NULL)
	{
		*hdoc_start = new_hdoc;
		return ;
	}
	last = *hdoc_start;
	while (last->hdoc_next)
		last = last->hdoc_next;
	last->hdoc_next = new_hdoc;
}

// Input resolution of heredocs sequantially, from hdoc collection
int	resolve_hdocs(t_redir *cur_hdoc, t_msh *ms)
{
	int	exstat;
	int	is_interactive;

	if (!cur_hdoc)
		return (EXIT_SUCCESS);
	exstat = EXIT_SUCCESS;
	is_interactive = isatty(STDIN_FILENO);
	while (cur_hdoc && exstat == EXIT_SUCCESS)
	{
		if (is_interactive)
			exstat = heredoc_isatty(cur_hdoc, ms);
		else
			heredoc_notatty(cur_hdoc, ms);
		cur_hdoc = cur_hdoc->hdoc_next;
	}
	return (exstat);
}
